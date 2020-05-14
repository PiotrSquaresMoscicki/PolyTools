#pragma once

#include <qmenubar.h>
#include <qtoolbar.h>

namespace pt
{
	// ************************************************************************************************
	class IActionsRegistry
	{
	public:
		virtual bool registerAction(std::string uniqueName, std::shared_ptr<QAction> action) = 0;
		 
		/* config format
		[
			{
			  "action": "SelectAll",
			  "shortcut": "ctrl + a"
			},
			{
			  "action": "ExpandAll",
			  "shortcut": "ctrl + m -> ctrl + o"
			},
			{
			  "action": "ExpandAll",
			  "shortcut": "ctrl + m -> ctrl + x"
			},
			{
			  "action": "Delete",
			  "shortcut": "delete || ctrl + backspace"
			}
		]
		*/
		virtual void refreshShortcuts(const std::string& config) = 0;

		/* config format
		[
			{
				"name": "File",
				"children": [
					{
					  "action": "Save"
					},
					{
					  "action": "Reload",
					  "name": "Reload from disk"
					},
					{
					  "action": "New scene"
					},
					{
					  "name": "Open",
					  "type": "Separator"
					},
					{
					  "action": "Open scene"
					},
					{
					  "name": "Save",
					  "type": "Separator"
					},
					{
					  "action": "Save",
					  "optional": "true",
					  "name": "Save scene as..."
					}
				]
			},
			{
				"name": "Edit",
				"children": [
					{
					  "action": "Undo",
					},
					{
					  "action": "Redo",
					}
				]
			}
		]
		*/
		virtual QMenuBar* createMenuBar(const std::string& config) = 0;

		/* config format
		[
			{
				"name": "File",
				"action": "Undo"
			},
			{
				"action": "Undo"
			},
			{
				"action": "Redo"
			}
		]
		*/
		virtual QToolBar* createToolBar(const std::string& config) = 0;
	};

} // namespace pt