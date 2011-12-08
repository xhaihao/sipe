/**
 * @file sipe-core-private.h
 *
 * pidgin-sipe
 *
 * Copyright (C) 2010-11 SIPE Project <http://sipe.sourceforge.net/>
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

/* Forward declarations */
struct sip_service_data;
struct sip_transport;
struct sipe_certificate;
struct sipe_media_call_private;
struct sipe_groupchat;
struct sipe_svc;

/**
 * Private part of the Sipe data structure
 *
 * This part contains the information only needed by the core
 */
struct sipe_account_data; /* to be removed... */
struct sipe_core_private {
	/**
	 * The public part is the first item, i.e. a pointer to the
	 * public part can also be used as a pointer to the private part.
	 */
	struct sipe_core_public public;

	/* sip-transport.c private data */
	struct sip_transport *transport;
	const struct sip_service_data *service_data;
	guint transport_type;

	/* SIPE protocol information */
	gchar *username;
	gchar *contact;
	gchar *epid;
	gchar *focus_factory_uri;
	GSList *sessions;
	GSList *sessions_to_accept;

	/* [MS-SIP] deltaNum counters */
	guint deltanum_contacts;
	guint deltanum_acl;      /* setACE (OCS2005 only) */

	/* Buddies */
	GSList *groups;
	GHashTable *buddies;

	/* Scheduling system */
	GSList *timeouts;

	/* Active subscriptions */
	GHashTable *subscriptions;

	/* Voice call */
	struct sipe_media_call_private *media_call;
	/**
	 *  Provides the necessary information on where we can obtain
	 *  credentials for the A/V Edge server service.
	 */
	gchar *mras_uri;
	gchar *media_relay_username;
	gchar *media_relay_password;
	GSList *media_relays;

	/* Group chat */
	struct sipe_groupchat *groupchat;

	/* @TODO: move to purple backend when menu code moves */
	GSList *blist_menu_containers;

	struct sipe_dns_query *dns_query;

	/* TLS-DSK: Certificates & Web services */
	struct sipe_certificate *certificate;
	struct sipe_svc *svc;

	/* the original data structure*/
	struct sipe_account_data *temporary;
};

/**
 * Flags - stored in sipe_core_public.flags but names not exported
 */
/* server is OCS2007+ */
#define SIPE_CORE_PRIVATE_FLAG_OCS2007          0x80000000
/* we are connected from outside the enterprise network boundary
 * via Edge Server */
#define SIPE_CORE_PRIVATE_FLAG_REMOTE_USER      0x40000000
/* multiple points of presence detected */
#define SIPE_CORE_PRIVATE_FLAG_MPOP             0x20000000
/* if there is support for batched subscription*/
#define SIPE_CORE_PRIVATE_FLAG_BATCHED_SUPPORT  0x10000000
/* if note is out-of-office note */
#define SIPE_CORE_PRIVATE_FLAG_OOF_NOTE         0x08000000
/* whether we published our initial state or not */
#define SIPE_CORE_PRIVATE_FLAG_INITIAL_PUBLISH  0x04000000
/* whether basic access level is set or not */
#define SIPE_CORE_PRIVATE_FLAG_ACCESS_LEVEL_SET 0x02000000

#define SIPE_CORE_PUBLIC_FLAG_IS(flag)    \
	((sipe_private->public.flags & SIPE_CORE_FLAG_ ## flag) == SIPE_CORE_FLAG_ ## flag)
#define SIPE_CORE_PUBLIC_FLAG_SET(flag)   \
	(sipe_private->public.flags |= SIPE_CORE_FLAG_ ## flag)
#define SIPE_CORE_PUBLIC_FLAG_UNSET(flag)				\
	(sipe_private->public.flags &= ~SIPE_CORE_FLAG_ ## flag)
#define SIPE_CORE_PRIVATE_FLAG_IS(flag)    \
	((sipe_private->public.flags & SIPE_CORE_PRIVATE_FLAG_ ## flag) == SIPE_CORE_PRIVATE_FLAG_ ## flag)
#define SIPE_CORE_PRIVATE_FLAG_SET(flag)   \
	(sipe_private->public.flags |= SIPE_CORE_PRIVATE_FLAG_ ## flag)
#define SIPE_CORE_PRIVATE_FLAG_UNSET(flag)				\
	(sipe_private->public.flags &= ~SIPE_CORE_PRIVATE_FLAG_ ## flag)

/* Convenience macros */
#define SIPE_CORE_PRIVATE ((struct sipe_core_private *)sipe_public)
#define SIPE_CORE_PUBLIC  ((struct sipe_core_public *)sipe_private)

/* Transition macros */
#define SIPE_ACCOUNT_DATA         SIPE_CORE_PRIVATE->temporary
#define SIPE_ACCOUNT_DATA_PRIVATE sipe_private->temporary

/**
 * sipe-core internal functions
 */
void sipe_core_connection_cleanup(struct sipe_core_private *sipe_private);

/*
  Local Variables:
  mode: c
  c-file-style: "bsd"
  indent-tabs-mode: t
  tab-width: 8
  End:
*/
