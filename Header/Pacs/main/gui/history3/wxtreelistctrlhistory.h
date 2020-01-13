/*
 *  
 *  $Id: wxtreelistctrlhistory.h $
 *  Ginkgo CADx Project
 *
 *  Copyright 2008-14 MetaEmotion S.L. All rights reserved.
 *  http://ginkgo-cadx.com
 *
 *  This file is licensed under LGPL v3 license.
 *  See License.txt for details
 *
 *
 */

#pragma once

#include <wx/intl.h>

#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/srchctrl.h>
#include <wx/sizer.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/treelistctrl/treelistctrl.h>
#include <wx/link_additions.h>
#include <wx/radiobut.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/statbox.h>
#include <wx/gbsizer.h>
#include <wx/button.h>
#include <wx/grid.h>
#include <wx/notebook.h>
#include <wx/dialog.h>
#include <wx/listbox.h>

#define COL_PATIENT_NAME	0
#define COL_PATIENT_ID		1
#define COL_AGE				2
#define COL_MODALITY			3
#define COL_DESCRIPTION		4
#define COL_DATE_TIME		5
#define COL_ACCNUMBER		6
#define COL_PENDING_TASKS	7
#define COL_LOCATION		8
#define COL_PK					9


class wxTreeListCtrlHistory : public wxTreeListCtrl
{
public:
	wxTreeListCtrlHistory(wxWindow *parent, wxWindowID id = -1,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = wxTR_DEFAULT_STYLE,
               const wxValidator &validator = wxDefaultValidator,
               const wxString& name = wxTreeListCtrlNameStr )
					: wxTreeListCtrl(parent, id, pos, size, style, validator, name)
    {
	}
	~wxTreeListCtrlHistory() {}

	virtual int OnCompareItems (const wxTreeItemId& item1, const wxTreeItemId& item2) 
	{
		if (item1.IsOk() && item2.IsOk()) {
			//by date...
			wxDateTime date1,date2;
			date1.ParseFormat(GetItemText(item1, COL_DATE_TIME), _("%m/%d/%Y %H:%M:%S"));
			date2.ParseFormat(GetItemText(item2, COL_DATE_TIME), _("%m/%d/%Y %H:%M:%S"));
			if (date1.IsValid() && date2.IsValid()) {
				wxTimeSpan diff = date1.Subtract(date2);
				if (diff.IsPositive()) {
					return 1;
				} else {
					return -1;
				}
			} else {
				return 0;
			}
		}
		return wxTreeListCtrl::OnCompareItems(item1, item2);
	}

	virtual int OnCompareItems (const wxTreeItemId& item1, const wxTreeItemId& item2, int column) 
	{
		int result = 0;
		if (item1.IsOk() && item2.IsOk()) {
			switch (column) {
				case COL_PATIENT_NAME:
				case COL_DESCRIPTION:
					{
						result = GetItemText(item1, column).CompareTo(GetItemText(item2, column), wxString::ignoreCase);
					}
					break;
				case COL_AGE:
					{
						long val1 = 0, val2 = 0;
						if (GetItemText(item1, column).ToLong(&val1) && GetItemText(item2, column).ToLong(&val2)) {
							if (val1 > val2) {
								result = 1;
							} else if (val1 < val2) {
								result = -1;
							} else {
								result = 0;
							}
						}
					}
					break;
				case COL_DATE_TIME:
					{
						//by date...
						wxDateTime date1,date2;
						date1.ParseFormat(GetItemText(item1, COL_DATE_TIME), _("%m/%d/%Y %H:%M:%S"));
						date2.ParseFormat(GetItemText(item2, COL_DATE_TIME), _("%m/%d/%Y %H:%M:%S"));
						if (date1.IsValid() && date2.IsValid()) {
							wxTimeSpan diff = date1.Subtract(date2);
							if (diff.IsPositive()) {
								result = 1;
							} else if (diff.IsEqualTo(wxTimeSpan(0))) {
								result = 0;
							} else {
								result = -1;
							}
						} else {
							if (date1.IsValid()) {
								result = 1;
							} else if (date2.IsValid()) {
								result = -1;
							} else {
								result = 0;
							}
						}
					}
					break;
				case COL_ACCNUMBER:
				case COL_PATIENT_ID:
				case COL_MODALITY:
				case COL_PENDING_TASKS:
				case COL_LOCATION:
				default:
					{
						//compare strings...
						result = GetItemText(item1, column).CompareTo(GetItemText(item2, column));
					}
					break;

			}
		}
		for (int i =0; result == 0 && i < 8; ++i) {
			result = GetItemText(item1, i).CompareTo(GetItemText(item2, i), wxString::ignoreCase);
		}
		return result;
	}
};
