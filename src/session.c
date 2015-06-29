/*
 * Copyright (C) 2015 Andrea Zagli <azagli@libero.it>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifdef HAVE_CONFIG_H
	#include <config.h>
#endif

#include <gio/gio.h>

#include <string.h>

#include "main.h"
#include "session.h"

static void zak_cgi_session_class_init (ZakCgiSessionClass *class);
static void zak_cgi_session_init (ZakCgiSession *zak_cgi_session);

static void zak_cgi_session_set_property (GObject *object,
                               guint property_id,
                               const GValue *value,
                               GParamSpec *pspec);
static void zak_cgi_session_get_property (GObject *object,
                               guint property_id,
                               GValue *value,
                               GParamSpec *pspec);

static void zak_cgi_session_dispose (GObject *gobject);
static void zak_cgi_session_finalize (GObject *gobject);

#define ZAK_CGI_SESSION_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), ZAK_CGI_TYPE_SESSION, ZakCgiSessionPrivate))

typedef struct _ZakCgiSessionPrivate ZakCgiSessionPrivate;
struct _ZakCgiSessionPrivate
	{
		gchar *sid;
		GFile *gfile;
		GKeyFile *kfile;
	};

G_DEFINE_TYPE (ZakCgiSession, zak_cgi_session, G_TYPE_OBJECT)

static void
zak_cgi_session_class_init (ZakCgiSessionClass *class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (class);

	object_class->set_property = zak_cgi_session_set_property;
	object_class->get_property = zak_cgi_session_get_property;
	object_class->dispose = zak_cgi_session_dispose;
	object_class->finalize = zak_cgi_session_finalize;

	g_type_class_add_private (object_class, sizeof (ZakCgiSessionPrivate));
}

static void
zak_cgi_session_init (ZakCgiSession *zak_cgi_session)
{
	ZakCgiSessionPrivate *priv = ZAK_CGI_SESSION_GET_PRIVATE (zak_cgi_session);

}

/**
 * zak_cgi_session_new:
 *
 * Returns: the newly created #ZakCgiSession object.
 */
ZakCgiSession
*zak_cgi_session_new (void)
{
	GHashTable *ht_cookies;

	GError *error;

	ZakCgiSession *zak_cgi_session;
	ZakCgiSessionPrivate *priv;

	zak_cgi_session = ZAK_CGI_SESSION (g_object_new (zak_cgi_session_get_type (), NULL));

	priv = ZAK_CGI_SESSION_GET_PRIVATE (zak_cgi_session);

	ht_cookies = zak_cgi_main_get_cookies ();
	priv->sid = g_hash_table_lookup (ht_cookies, "ZAKCGISID");

	if (priv->sid != NULL)
		{
			/* open the file */
			priv->gfile = g_file_new_for_path (g_build_filename (g_get_tmp_dir (), priv->sid, NULL));

			error = NULL;

			/* TODO */
			/* check the content */
			priv->kfile = g_key_file_new ();
			if (!g_key_file_load_from_file (priv->kfile,
			                                g_file_get_path (priv->gfile),
			                                G_KEY_FILE_NONE,
			                                &error)
			    || error != NULL)
				{
					/* TODO */
				}
		}

	return zak_cgi_session;
}

/**
 * zak_cgi_session_get_header:
 * @session:
 *
 * Returns: the header that set the cookie session, if needed; else an empty string.
 */
gchar
*zak_cgi_session_get_header (ZakCgiSession *session)
{
	gchar *ret;

	GError *error;
	GFileIOStream *iostream;

	ZakCgiSessionPrivate *priv = ZAK_CGI_SESSION_GET_PRIVATE (session);

	if (priv->sid == NULL)
		{
			/* create new random name */
			guint32 i;
			gchar *tmp;

			i = g_random_int ();

			tmp = g_strdup_printf ("%d", i);
			
			priv->sid = g_compute_checksum_for_string (G_CHECKSUM_MD5,
			                                           tmp,
			                                           strlen (tmp));

			g_free (tmp);

			/* see if file already exists */
			priv->gfile = g_file_new_for_path (g_build_filename (g_get_tmp_dir (), priv->sid, NULL));
			error = NULL;
			iostream = g_file_replace_readwrite (priv->gfile, NULL, FALSE, G_FILE_CREATE_PRIVATE, NULL, &error);
			if (iostream == NULL
			    || error != NULL)
				{
					/* TODO */
				}
			else
				{
					/* TODO */
					/* insert some data (ex IP) */
					g_io_stream_close (G_IO_STREAM (iostream), NULL, NULL);
					g_object_unref (iostream);
				}

			ret = zak_cgi_main_set_cookie ("ZAKCGISID", priv->sid, NULL, NULL, NULL, FALSE, FALSE);
		}
	else
		{
			ret = g_strdup ("");
		}

	return ret;
}

/**
 * zak_cgi_session_set_value:
 * @session:
 * @name:
 * @value:
 *
 */
void
zak_cgi_session_set_value (ZakCgiSession *session, const gchar *name, const gchar *value)
{
	ZakCgiSessionPrivate *priv = ZAK_CGI_SESSION_GET_PRIVATE (session);

	if (priv->kfile != NULL)
		{
			g_key_file_set_value (priv->kfile, "SESSION", name, value);
			g_key_file_save_to_file (priv->kfile, g_file_get_path (priv->gfile), NULL);
		}
}

/**
 * zak_cgi_session_get_value:
 * @session:
 * @name:
 *
 * Returns: a value from session.
 */
gchar
*zak_cgi_session_get_value (ZakCgiSession *session, const gchar *name)
{
	gchar *ret;

	ZakCgiSessionPrivate *priv = ZAK_CGI_SESSION_GET_PRIVATE (session);

	ret = NULL;
	if (priv->kfile != NULL)
		{
			ret = g_key_file_get_value (priv->kfile, "SESSION", name, NULL);
		}

	return ret;
}

/* PRIVATE */
static void
zak_cgi_session_set_property (GObject *object,
                   guint property_id,
                   const GValue *value,
                   GParamSpec *pspec)
{
	ZakCgiSession *zak_cgi_session = (ZakCgiSession *)object;
	ZakCgiSessionPrivate *priv = ZAK_CGI_SESSION_GET_PRIVATE (zak_cgi_session);

	switch (property_id)
		{
			default:
				G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
				break;
		}
}

static void
zak_cgi_session_get_property (GObject *object,
                   guint property_id,
                   GValue *value,
                   GParamSpec *pspec)
{
	ZakCgiSession *zak_cgi_session = (ZakCgiSession *)object;
	ZakCgiSessionPrivate *priv = ZAK_CGI_SESSION_GET_PRIVATE (zak_cgi_session);

	switch (property_id)
		{
			default:
				G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
				break;
		}
}

static void
zak_cgi_session_dispose (GObject *gobject)
{
	ZakCgiSession *zak_cgi_session = (ZakCgiSession *)gobject;
	ZakCgiSessionPrivate *priv = ZAK_CGI_SESSION_GET_PRIVATE (zak_cgi_session);


	GObjectClass *parent_class = g_type_class_peek_parent (G_OBJECT_GET_CLASS (gobject));
	parent_class->dispose (gobject);
}

static void
zak_cgi_session_finalize (GObject *gobject)
{
	ZakCgiSession *zak_cgi_session = (ZakCgiSession *)gobject;
	ZakCgiSessionPrivate *priv = ZAK_CGI_SESSION_GET_PRIVATE (zak_cgi_session);


	GObjectClass *parent_class = g_type_class_peek_parent (G_OBJECT_GET_CLASS (gobject));
	parent_class->finalize (gobject);
}