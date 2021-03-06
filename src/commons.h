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

#ifndef __ZAK_CGI_COMMONS_H__
#define __ZAK_CGI_COMMONS_H__


#include <glib-object.h>

#include "main.h"


GHashTable *zak_cgi_commons_valist_to_ghashtable (va_list ap);

gchar *zak_cgi_commons_ghashtable_to_str_attrs (GHashTable *ht);


#endif /* __ZAK_CGI_COMMONS_H__ */
