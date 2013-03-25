/**
 * @file sipe-http.h
 *
 * pidgin-sipe
 *
 * Copyright (C) 2013 SIPE Project <http://sipe.sourceforge.net/>
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* Public interface to HTTP request service */

/*
 * Interface dependencies:
 *
 * <glib.h>
 */

/* Forward declarations */
struct sipe_core_private;
struct sipe_http_request;

/**
 * Free HTTP data
 *
 * @param sipe_private SIPE core private data
 */
void sipe_http_free(struct sipe_core_private *sipe_private);

/**
 * Cancel pending HTTP request
 *
 * @param pointer to opaque HTTP request data structure
 */
void sipe_http_request_cancel(struct sipe_http_request *request);

/**
 * Create HTTP GET request
 *
 * @param sipe_private SIPE core private data
 * @param uri          URI
 * @param headers      additional headers (may be @c NULL)
 *
 * @return pointer to opaque HTTP request data structure (@c NULL if failed)
 */
struct sipe_http_request *sipe_http_request_get(struct sipe_core_private *sipe_private,
						const gchar *uri,
						const gchar *headers);

/**
 * Create HTTP POST request
 *
 * @param sipe_private SIPE core private data
 * @param uri          URI
 * @param headers      additional headers (may be @c NULL)
 * @param body         body contents
 * @param content_type body content type
 *
 * @return pointer to opaque HTTP request data structure (@c NULL if failed)
 */
struct sipe_http_request *sipe_http_request_post(struct sipe_core_private *sipe_private,
						 const gchar *uri,
						 const gchar *headers,
						 const gchar *body,
						 const gchar *content_type);