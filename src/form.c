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

#include <syslog.h>

#include "form.h"

static void zak_cgi_form_class_init (ZakCgiFormClass *class);
static void zak_cgi_form_init (ZakCgiForm *zak_cgi_form);

static void zak_cgi_form_set_property (GObject *object,
                               guint property_id,
                               const GValue *value,
                               GParamSpec *pspec);
static void zak_cgi_form_get_property (GObject *object,
                               guint property_id,
                               GValue *value,
                               GParamSpec *pspec);

static void zak_cgi_form_dispose (GObject *gobject);
static void zak_cgi_form_finalize (GObject *gobject);

#define ZAK_CGI_FORM_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), ZAK_CGI_TYPE_FORM, ZakCgiFormPrivate))

typedef struct _ZakCgiFormPrivate ZakCgiFormPrivate;
struct _ZakCgiFormPrivate
	{
		ZakCgiMain *zakcgimain;
		GHashTable *ht_elems;
	};

G_DEFINE_TYPE (ZakCgiForm, zak_cgi_form, G_TYPE_OBJECT)

static void
zak_cgi_form_class_init (ZakCgiFormClass *class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (class);

	object_class->set_property = zak_cgi_form_set_property;
	object_class->get_property = zak_cgi_form_get_property;
	object_class->dispose = zak_cgi_form_dispose;
	object_class->finalize = zak_cgi_form_finalize;

	g_type_class_add_private (object_class, sizeof (ZakCgiFormPrivate));
}

static void
zak_cgi_form_init (ZakCgiForm *zak_cgi_form)
{
	ZakCgiFormPrivate *priv = ZAK_CGI_FORM_GET_PRIVATE (zak_cgi_form);

	priv->zakcgimain = NULL;
	priv->ht_elems = g_hash_table_new (g_str_hash, g_str_equal);
}

/**
 * zak_cgi_form_new:
 * @zakcgimain:
 *
 * Returns: the newly created #ZakCgiForm object.
 */
ZakCgiForm
*zak_cgi_form_new (ZakCgiMain *zakcgimain)
{
	ZakCgiForm *zak_cgi_form;
	ZakCgiFormPrivate *priv;

	zak_cgi_form = ZAK_CGI_FORM (g_object_new (zak_cgi_form_get_type (), NULL));

	priv = ZAK_CGI_FORM_GET_PRIVATE (zak_cgi_form);
	priv->zakcgimain = zakcgimain;

	return zak_cgi_form;
}

/**
 * zak_cgi_form_add_element:
 * @zakcgiform:
 * @element:
 *
 * Returns: #TRUE if @element is added; FALSE otherwise.
 */
gboolean
zak_cgi_form_add_element (ZakCgiForm *zakcgiform, ZakCgiFormElement *element)
{
	gboolean ret;
	gchar *id;

	ZakCgiFormPrivate *priv;

	priv = ZAK_CGI_FORM_GET_PRIVATE (zakcgiform);

	id = zak_cgi_form_element_get_id (element);

	if (g_hash_table_lookup (priv->ht_elems, id))
		{
			g_warning ("You cannot add an element with id already present in the form.");
			ret = FALSE;
		}
	else
		{
			g_hash_table_insert (priv->ht_elems, g_strdup (id), element);
			ret = TRUE;
		}

	g_free (id);

	return ret;
}

/* PRIVATE */
static void
zak_cgi_form_set_property (GObject *object,
                   guint property_id,
                   const GValue *value,
                   GParamSpec *pspec)
{
	ZakCgiForm *zak_cgi_form = (ZakCgiForm *)object;
	ZakCgiFormPrivate *priv = ZAK_CGI_FORM_GET_PRIVATE (zak_cgi_form);

	switch (property_id)
		{
			default:
				G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
				break;
		}
}

static void
zak_cgi_form_get_property (GObject *object,
                   guint property_id,
                   GValue *value,
                   GParamSpec *pspec)
{
	ZakCgiForm *zak_cgi_form = (ZakCgiForm *)object;
	ZakCgiFormPrivate *priv = ZAK_CGI_FORM_GET_PRIVATE (zak_cgi_form);

	switch (property_id)
		{
			default:
				G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
				break;
		}
}

static void
zak_cgi_form_dispose (GObject *gobject)
{
	ZakCgiForm *zak_cgi_form = (ZakCgiForm *)gobject;
	ZakCgiFormPrivate *priv = ZAK_CGI_FORM_GET_PRIVATE (zak_cgi_form);


	GObjectClass *parent_class = g_type_class_peek_parent (G_OBJECT_GET_CLASS (gobject));
	parent_class->dispose (gobject);
}

static void
zak_cgi_form_finalize (GObject *gobject)
{
	ZakCgiForm *zak_cgi_form = (ZakCgiForm *)gobject;
	ZakCgiFormPrivate *priv = ZAK_CGI_FORM_GET_PRIVATE (zak_cgi_form);


	GObjectClass *parent_class = g_type_class_peek_parent (G_OBJECT_GET_CLASS (gobject));
	parent_class->finalize (gobject);
}