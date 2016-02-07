/*
 * Copyright (C) 2016 Andrea Zagli <azagli@libero.it>
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

#ifndef __ZAK_CGI_FORM_ELEMENT_EMAIL_H__
#define __ZAK_CGI_FORM_ELEMENT_EMAIL_H__


#include <glib-object.h>

#include <libxml/tree.h>

#include "formelement.h"


G_BEGIN_DECLS


#define ZAK_CGI_TYPE_FORM_ELEMENT_EMAIL                 (zak_cgi_form_element_email_get_type ())
#define ZAK_CGI_FORM_ELEMENT_EMAIL(obj)                 (G_TYPE_CHECK_INSTANCE_CAST ((obj), ZAK_CGI_TYPE_FORM_ELEMENT_EMAIL, ZakCgiFormElementEmail))
#define ZAK_CGI_FORM_ELEMENT_EMAIL_CLASS(klass)         (G_TYPE_CHECK_CLASS_CAST ((klass), ZAK_CGI_TYPE_FORM_ELEMENT_EMAIL, ZakCgiFormElementEmailClass))
#define ZAK_CGI_IS_FORM_ELEMENT_EMAIL(obj)              (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ZAK_CGI_TYPE_FORM_ELEMENT_EMAIL))
#define ZAK_CGI_IS_FORM_ELEMENT_EMAIL_CLASS(klass)      (G_TYPE_CHECK_CLASS_TYPE ((klass), ZAK_CGI_TYPE_FORM_ELEMENT_EMAIL))
#define ZAK_CGI_FORM_ELEMENT_EMAIL_GET_CLASS(obj)       (G_TYPE_INSTANCE_GET_CLASS ((obj), ZAK_CGI_TYPE_FORM_ELEMENT_EMAIL, ZakCgiFormElementEmailClass))

typedef struct _ZakCgiFormElementEmail ZakCgiFormElementEmail;
typedef struct _ZakCgiFormElementEmailClass ZakCgiFormElementEmailClass;

struct _ZakCgiFormElementEmail
	{
		ZakCgiFormElement parent_instance;
	};

struct _ZakCgiFormElementEmailClass
	{
		ZakCgiFormElementClass parent_class;
	};


GType zak_cgi_form_element_email_get_type (void);

ZakCgiFormElement *zak_cgi_form_element_email_new ();
ZakCgiFormElement *zak_cgi_form_element_email_new_attrs (const gchar *id, ...);

gboolean zak_cgi_form_element_email_xml_parsing (ZakFormElement *element, xmlNodePtr xmlnode);


G_END_DECLS


#endif /* __ZAK_CGI_FORM_ELEMENT_EMAIL_H__ */
