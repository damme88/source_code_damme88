// CustomCombo.cpp : implementation file
//

#include "stdafx.h"
#include "Simple_Draw.h"
#include "CustomCombo.h"


// CustomCombo

IMPLEMENT_DYNAMIC(CustomCombo, CComboBox)

CustomCombo::CustomCombo()
{

}

CustomCombo::~CustomCombo()
{
}


BEGIN_MESSAGE_MAP(CustomCombo, CComboBox)
END_MESSAGE_MAP()



// CustomCombo message handlers

INT_PTR CustomCombo::AddItemCombo(LPCTSTR lpszitem) {
  AddString(lpszitem);
  return 1;
}

void CustomCombo::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
   unsigned int num = GetCount();
   if (!num)
	   return;
   if (lpDrawItemStruct->itemID >= num || lpDrawItemStruct->itemID < 0) {
     str = "";
   } else {
     str = (LPTSTR)lpDrawItemStruct->itemData;
   }

   CDC dc;
   dc.Attach(lpDrawItemStruct->hDC);

   // Save these value to restore them when done drawing.
   COLORREF crOldTextColor = dc.GetTextColor();
   COLORREF crOldBkColor = dc.GetBkColor();

   // If this item is selected, set the background color 
   // and the text color to appropriate values. Erase
   // the rect by filling it with the background color.
   if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&
      (lpDrawItemStruct->itemState  & ODS_SELECTED))
   {
      dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
      dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
      dc.FillSolidRect(&lpDrawItemStruct->rcItem, ::GetSysColor(COLOR_HIGHLIGHT));
   }
   else
      dc.FillSolidRect(&lpDrawItemStruct->rcItem, crOldBkColor);

   CRect rect(lpDrawItemStruct->rcItem);
   rect.DeflateRect(1,0);

   HICON hIcon = NULL;
   BOOL bold = FALSE;
   ITEMDATA iData;
   if (myMap.Lookup(lpDrawItemStruct->itemID,iData))
   {
	   hIcon = iData.icon;
   }

   DrawIconEx(dc.GetSafeHdc(),rect.left,rect.top,hIcon,0, 0, 0, NULL, DI_NORMAL);

   rect.left += 17;

  // Draw the text.
   dc.DrawText(
      str,
      -1,
      &rect,
      DT_LEFT|DT_SINGLELINE|DT_VCENTER);

   // Reset the background color and the text color back to their
   // original values.
   dc.SetTextColor(crOldTextColor);
   dc.SetBkColor(crOldBkColor);

   dc.Detach();

}




void CustomCombo::MeasureItem(LPMEASUREITEMSTRUCT) { 
  return;
}

int CustomCombo::CompareItem(LPCOMPAREITEMSTRUCT) {
  return 0; 
}

