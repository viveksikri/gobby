/* Gobby - GTK-based collaborative text editor
 * Copyright (C) 2008-2014 Armin Burgmeier <armin@arbur.net>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _GOBBY_BROWSER_COMMANDS_HPP_
#define _GOBBY_BROWSER_COMMANDS_HPP_

#include "operations/operations.hpp"
#include "core/browser.hpp"
#include "core/statusbar.hpp"

#include <sigc++/trackable.h>

namespace Gobby
{

class BrowserCommands: public sigc::trackable
{
public:
	BrowserCommands(Browser& browser, FolderManager& folder_manager,
	                StatusBar& status_bar, Operations& operations,
	                const Preferences& preferences);
	~BrowserCommands();

protected:
	static void
	on_set_browser_static(InfGtkBrowserModel* model,
	                      GtkTreePath* path,
	                      GtkTreeIter* iter,
	                      InfBrowser* old_browser,
	                      InfBrowser* new_browser,
	                      gpointer user_data)
	{
		static_cast<BrowserCommands*>(user_data)->
			on_set_browser(model, iter, old_browser, new_browser);
	}

	void on_set_browser(InfGtkBrowserModel* model, GtkTreeIter* iter,
	                    InfBrowser* old_browser, InfBrowser* new_browser);
	void on_notify_status(InfBrowser* browser);

	void subscribe_chat(InfBrowser* browser);
	bool create_chat_document(InfBrowser* browser);

	void on_connect(const Glib::ustring& hostname);
	void on_activate(InfBrowser* browser, InfBrowserIter* iter);

	void on_finished(InfRequest* request,
	                 InfBrowser* browser,
	                 const InfBrowserIter* iter,
	                 const GError* error);

	Browser& m_browser;
	FolderManager& m_folder_manager;
	StatusBar& m_status_bar;
	Operations& m_operations;
	const Preferences& m_preferences;
	gulong m_set_browser_handler;

	class BrowserInfo;
	typedef std::map<InfBrowser*, BrowserInfo*> BrowserMap;
	BrowserMap m_browser_map;

	class RequestInfo;
	typedef std::map<InfRequest*, RequestInfo*> RequestMap;
	RequestMap m_request_map;
};

}

#endif // _GOBBY_BROWSER_COMMANDS_HPP_
