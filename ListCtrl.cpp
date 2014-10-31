// ListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "WinDE.h"
#include "ListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ListCtrl

ListCtrl::ListCtrl()
{
	m_nHighlight = HIGHLIGHT_ROW;
}

ListCtrl::~ListCtrl()
{
}


BEGIN_MESSAGE_MAP(ListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(ListCtrl)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ListCtrl message handlers

BOOL ListCtrl::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style &= ~LVS_TYPEMASK;
    cs.style &= ~LVS_SHOWSELALWAYS;
    cs.style |= LVS_REPORT | LVS_OWNERDRAWFIXED;
    //cs.style |= LVS_EDITLABELS;
	m_nHighlight = HIGHLIGHT_ROW;
    return(CListCtrl::PreCreateWindow(cs));
}


void ListCtrl::OnPaint() 
{
	// in full row select mode, we need to extend the clipping region
    // so we can paint a selection all the way to the right
    if (m_nHighlight == HIGHLIGHT_ROW &&
        (GetStyle() & LVS_TYPEMASK) == LVS_REPORT )
    {
        CRect rcBounds;
        GetItemRect(0, rcBounds, LVIR_BOUNDS);
        
        CRect rcClient;
        GetClientRect(&rcClient);
        if(rcBounds.right < rcClient.right)
        {
            CPaintDC dc(this);
            
            CRect rcClip;
            dc.GetClipBox(rcClip);
            
            rcClip.left = min(rcBounds.right-1, rcClip.left);
            rcClip.right = rcClient.right;
            
            InvalidateRect(rcClip, FALSE);
        }
    }
}

void ListCtrl::OnSetFocus(CWnd* pOldWnd) 
{
   CListCtrl::OnSetFocus(pOldWnd);
    
    // check if we are getting focus from label edit box
    if(pOldWnd!=NULL && pOldWnd->GetParent()==this)
        return;
    
    // repaint items that should change appearance
    if((GetStyle() & LVS_TYPEMASK)==LVS_REPORT)
        RepaintSelectedItems();
	
}

void ListCtrl::OnKillFocus(CWnd* pNewWnd) 
{	
	  CListCtrl::OnKillFocus(pNewWnd);
    
    // check if we are losing focus to label edit box
    if(pNewWnd != NULL && pNewWnd->GetParent() == this)
        return;
    
    // repaint items that should change appearance
    if((GetStyle() & LVS_TYPEMASK) == LVS_REPORT)
        RepaintSelectedItems();
	
}

void ListCtrl::RepaintSelectedItems()
{
    CRect rcBounds, rcLabel;
    
    // Invalidate focused item so it can repaint 
    int nItem = GetNextItem(-1, LVNI_FOCUSED);
    
    if(nItem != -1)
    {
        GetItemRect(nItem, rcBounds, LVIR_BOUNDS);
        GetItemRect(nItem, rcLabel, LVIR_LABEL);
        rcBounds.left = rcLabel.left;
        
        InvalidateRect(rcBounds, FALSE);
    }
    
    // Invalidate selected items depending on LVS_SHOWSELALWAYS
    if(!(GetStyle() & LVS_SHOWSELALWAYS))
    {
        for(nItem = GetNextItem(-1, LVNI_SELECTED);
        nItem != -1; nItem = GetNextItem(nItem, LVNI_SELECTED))
        {
            GetItemRect(nItem, rcBounds, LVIR_BOUNDS);
            GetItemRect(nItem, rcLabel, LVIR_LABEL);
            rcBounds.left = rcLabel.left;
            
            InvalidateRect(rcBounds, FALSE);
        }
    }
    
    UpdateWindow();
}

int ListCtrl::SetHighlightType(EHighlight hilite)
{
    int oldhilite = m_nHighlight;
    if( hilite <= HIGHLIGHT_ROW )
    {
        m_nHighlight = hilite;
        Invalidate();
    }
    return oldhilite;
}

void ListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
    CRect rcItem(lpDrawItemStruct->rcItem);
    int nItem = lpDrawItemStruct->itemID;
    CImageList* pImageList;
    
    // Save dc state
    int nSavedDC = pDC->SaveDC();
    
    // Get item image and state info
    LV_ITEM lvi;
    lvi.mask = LVIF_IMAGE | LVIF_STATE;
    lvi.iItem = nItem;
    lvi.iSubItem = 0;
    lvi.stateMask = 0xFFFF;     // get all state flags
    GetItem(&lvi);
    
    // Should the item be highlighted
    BOOL bHighlight =((lvi.state & LVIS_DROPHILITED)
        || ( (lvi.state & LVIS_SELECTED)
        && ((GetFocus() == this)
        || (GetStyle() & LVS_SHOWSELALWAYS)
        )
        )
        );
    
    // Get rectangles for drawing
    CRect rcBounds, rcLabel, rcIcon;
    GetItemRect(nItem, rcBounds, LVIR_BOUNDS);
    GetItemRect(nItem, rcLabel, LVIR_LABEL);
    GetItemRect(nItem, rcIcon, LVIR_ICON);
    CRect rcCol( rcBounds ); 
    
    CString sLabel = GetItemText( nItem, 0 );
    
    // Labels are offset by a certain amount  
    // This offset is related to the width of a space character
    int offset = pDC->GetTextExtent(_T(" "), 1 ).cx*2;
    
    CRect rcHighlight;
    CRect rcWnd;
    int nExt;
    switch( m_nHighlight )
    {
    case 0: 
        nExt = pDC->GetOutputTextExtent(sLabel).cx + offset;
        rcHighlight = rcLabel;
        if( rcLabel.left + nExt < rcLabel.right )
            rcHighlight.right = rcLabel.left + nExt;
        break;
    case 1:
        rcHighlight = rcBounds;
        rcHighlight.left = rcLabel.left;
        break;
    case 2:
        GetClientRect(&rcWnd);
        rcHighlight = rcBounds;
        rcHighlight.left = rcLabel.left;
        rcHighlight.right = rcWnd.right;
        break;
    default:
        rcHighlight = rcLabel;
    }
    
    // Draw the background color
    if( bHighlight )
    {
        pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
        pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
        
        pDC->FillRect(rcHighlight, &CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
    }
    else
        pDC->FillRect(rcHighlight, &CBrush(::GetSysColor(COLOR_WINDOW)));
    
    // Set clip region
    rcCol.right = rcCol.left + GetColumnWidth(0);
    CRgn rgn;
    rgn.CreateRectRgnIndirect(&rcCol);
    pDC->SelectClipRgn(&rgn);
    rgn.DeleteObject();
    
    // Draw state icon
    if (lvi.state & LVIS_STATEIMAGEMASK)
    {
        int nImage = ((lvi.state & LVIS_STATEIMAGEMASK)>>12) - 1;
        pImageList = GetImageList(LVSIL_STATE);
        if (pImageList)
        {
            pImageList->Draw(pDC, nImage,
                CPoint(rcCol.left, rcCol.top), ILD_TRANSPARENT);
        }
    }
    
    // Draw normal and overlay icon
    pImageList = GetImageList(LVSIL_SMALL);
    if (pImageList)
    {
        UINT nOvlImageMask=lvi.state & LVIS_OVERLAYMASK;
        pImageList->Draw(pDC, lvi.iImage, 
            CPoint(rcIcon.left, rcIcon.top),
            (bHighlight?ILD_BLEND50:0) | ILD_TRANSPARENT | nOvlImageMask );
    }
    
    // Draw item label - Column 0
    rcLabel.left += offset/2;
    rcLabel.right -= offset;
    
    pDC->DrawText(sLabel,-1,rcLabel,
        DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP |
        DT_VCENTER | DT_END_ELLIPSIS);
    
    // Draw labels for remaining columns
    LV_COLUMN lvc;
    lvc.mask = LVCF_FMT | LVCF_WIDTH;
    
    if( m_nHighlight == 0 )     // Highlight only first column
    {
        pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
        pDC->SetBkColor(::GetSysColor(COLOR_WINDOW));
    }
    
    rcBounds.right = rcHighlight.right > rcBounds.right ? rcHighlight.right :
    rcBounds.right;
    rgn.CreateRectRgnIndirect(&rcBounds);
    pDC->SelectClipRgn(&rgn);
    
    for(int nColumn = 1; GetColumn(nColumn, &lvc); nColumn++)
    {
        rcCol.left = rcCol.right;
        rcCol.right += lvc.cx;
        
        // Draw the background if needed
        if( m_nHighlight == HIGHLIGHT_NORMAL )
            pDC->FillRect(rcCol, &CBrush(::GetSysColor(COLOR_WINDOW)));
        
        sLabel = GetItemText(nItem, nColumn);
        if (sLabel.GetLength() == 0)
            continue;
        
        // Get the text justification
        UINT nJustify = DT_LEFT;
        switch(lvc.fmt & LVCFMT_JUSTIFYMASK)
        {
        case LVCFMT_RIGHT:
            nJustify = DT_RIGHT;
            break;
        case LVCFMT_CENTER:
            nJustify = DT_CENTER;
            break;
        default:
            break;
        }
        
        rcLabel = rcCol;
        rcLabel.left += offset;
        rcLabel.right -= offset;
        
        pDC->DrawText(sLabel, -1, rcLabel, nJustify | DT_SINGLELINE | 
            DT_NOPREFIX | DT_VCENTER | DT_END_ELLIPSIS);
    }
    
    // Draw focus rectangle if item has focus
    if (lvi.state & LVIS_FOCUSED && (GetFocus() == this))
        pDC->DrawFocusRect(rcHighlight);
    
    // Restore dc
    pDC->RestoreDC( nSavedDC );

}
