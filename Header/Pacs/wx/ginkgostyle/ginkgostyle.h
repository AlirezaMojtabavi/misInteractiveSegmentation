/*
 *
 *  $Id$
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
#include <api/api.h>
#include <wx/scrolwin.h>
#include <wx/panel.h>
#include <wx/bitmap.h>

class wxAuiToolBar;

class EXTAPI VerticalHeader: public wxPanel {
public:
	VerticalHeader(wxWindow *parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTAB_TRAVERSAL ,
				const wxString& titulo = wxEmptyString);
	~VerticalHeader();

	virtual void SetToolTip(const wxString& tip);
	virtual void SetTitle(const wxString& titulo);

protected:
	virtual void OnEraseBackground( wxEraseEvent& event );
	virtual void OnPaint(wxPaintEvent &event);
	virtual void OnSize(wxSizeEvent &event);

	wxColour m_colorBorde;
	wxColour m_colorSombraBorde;
	wxColour m_colorTitulo;
	wxColour m_colorTituloInactivo;
	wxColour m_fondoTituloTopColor;
	wxColour m_fondoTituloBottomColor;
	wxString m_titulo;
	wxFont m_fuente;
	int m_AlturaCabecera;

	int m_sizeBorder;
};

class EXTAPI HeaderPanelWithButton: public wxPanel {
public:
	HeaderPanelWithButton(wxWindow *parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTAB_TRAVERSAL | wxNO_BORDER,
				const wxString& titulo = wxEmptyString);
	~HeaderPanelWithButton();

	virtual void SetToolTip(const wxString& tip);
	virtual void SetTitle(const wxString& titulo);
	virtual void Realize();
	wxAuiToolBar* GetButtonBar();

protected:
	wxColour m_barColor;
	wxFont m_fontBar;
	wxAuiToolBar* m_pTittleBar;
	wxAuiToolBar* m_pButtonBar;
};

class EXTAPI SubHeaderPanelWithButton: public HeaderPanelWithButton {
public:
	SubHeaderPanelWithButton(wxWindow *parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTAB_TRAVERSAL | wxNO_BORDER,
				const wxString& titulo = wxT(""));
	~SubHeaderPanelWithButton();
};

class EXTAPI HeaderPanel: public wxPanel {
public:
	HeaderPanel(wxWindow *parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTAB_TRAVERSAL | wxNO_BORDER,
				const wxString& titulo = wxT(""));
	~HeaderPanel();

	virtual void SetSubtitle(const wxString& subtitle);

	virtual void SetToolTip(const wxString& tip);
	virtual void SetTitle(const wxString& titulo);

	virtual bool Enable(bool enabled);

	virtual void OnEraseBackground( wxEraseEvent& event );
	virtual void OnPaint(wxPaintEvent &event);
	virtual void OnSize(wxSizeEvent &event);

protected:
	wxColour m_colorBorde;
	wxColour m_colorSombraBorde;
	wxColour m_colorTitulo;
	wxColour m_colorTituloInactivo;
	wxColour m_fondoTituloTopColor;
	wxColour m_fondoTituloBottomColor;
	wxString m_titulo;
	wxFont m_fuente;
	int m_AlturaCabecera;

	int m_sizeBorder;

	wxBitmap m_bitmap;
	wxString m_subtitle;
	wxFont m_fuenteSubTitle;
};




class EXTAPI PanelScrollable: public wxScrolledWindow {
public:
	PanelScrollable(wxWindow *parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTAB_TRAVERSAL | wxNO_BORDER);
	~PanelScrollable();
};


class EXTAPI BodyPanel: public PanelScrollable {
public:
	BodyPanel(wxWindow *parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTAB_TRAVERSAL | wxNO_BORDER);
	~BodyPanel();

	void SetSizer(wxSizer* sizer, bool deleteOld = true);

protected:
	int m_sizeBorderInterior;
	wxColour m_colorFondo;
};

class EXTAPI BodyPanelSinScroll: public wxPanel {
public:
	BodyPanelSinScroll(wxWindow *parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTAB_TRAVERSAL | wxNO_BORDER);
	~BodyPanelSinScroll();

	void SetSizer(wxSizer* sizer, bool deleteOld = true);

protected:
	int m_sizeBorderInterior;
	wxColour m_colorFondo;
};

class EXTAPI FooterPanel: public wxPanel {
public:
	FooterPanel(wxWindow *parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTAB_TRAVERSAL | wxNO_BORDER);
	~FooterPanel();

	void SetSizer(wxSizer* sizer, bool deleteOld = true);

	virtual void OnEraseBackground( wxEraseEvent& event );
	virtual void OnPaint(wxPaintEvent &event);

protected:
	int m_sizeBorderInterior;
	wxColour m_colorBorde;
	int m_sizeBorder;
};


class EXTAPI TitledPanel: public wxPanel {
public:
	TitledPanel(wxWindow *parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTAB_TRAVERSAL | wxNO_BORDER,
				const wxString& titulo = wxT(""));
	~TitledPanel();
	virtual void SetToolTip(const wxString& tip);
	virtual void SetTitle(const wxString& titulo);

	virtual bool Enable(bool enabled);

	virtual void OnEraseBackground( wxEraseEvent& event );
	virtual void OnPaint(wxPaintEvent &event);
	virtual void OnSize(wxSizeEvent &event);

	virtual void SetColorBorde(const wxColour& colorBorde);
	virtual wxColour GetColorBorde();

	virtual void SetColorTitulo(const wxColour& colorBorde);
	virtual wxColour GetColorTitulo();

	virtual int GetSizeBorde();
	virtual void SetSizeBorde(int size);

	virtual int GetBorderInterior();
	virtual void SetBorderInterior(int size);

	virtual bool SetBackgroundColour(const wxColour& colour);

	virtual void Recoger(bool recoger = true);

	virtual bool EstaRecogido();

	virtual int GetGap();

	void SetSizer(wxSizer* sizer, bool deleteOld = true);

protected:
	bool		m_recogido;
	wxColour m_colorFondo;
	wxColour m_colorBorde;
	wxColour m_colorSombraBorde;
	wxColour m_colorTitulo;
	wxColour m_colorTituloInactivo;
	wxColour m_fondoTituloTopColor;
	wxColour m_fondoTituloBottomColor;
	wxString m_titulo;
	wxFont m_fuente;
	int m_margenTitulo;
	int m_sizeBorder;
	int m_borderInterior;
};

class EXTAPI TitledPanelSinBorder: public TitledPanel {
public:
	TitledPanelSinBorder(wxWindow *parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTAB_TRAVERSAL | wxNO_BORDER,
				const wxString& titulo = wxT(""));
	~TitledPanelSinBorder();
};


class EXTAPI TitledPanelSeparatorV: public wxPanel {
public:
	TitledPanelSeparatorV(wxWindow *parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxNO_BORDER);
	~TitledPanelSeparatorV();

protected:
	int m_separacion;
};

class EXTAPI TitledPanelSeparatorH: public wxPanel {
public:
	TitledPanelSeparatorH(wxWindow *parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxNO_BORDER);
	~TitledPanelSeparatorH();

protected:
	int m_separacion;
};

class EXTAPI SubTitledPanel: public TitledPanel {
public:
	SubTitledPanel(wxWindow *parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTAB_TRAVERSAL | wxNO_BORDER,
				const wxString& titulo = wxT(""));
	~SubTitledPanel();
};

class EXTAPI SubTitledPanelSinBorder: public SubTitledPanel {
public:
	SubTitledPanelSinBorder(wxWindow *parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTAB_TRAVERSAL | wxNO_BORDER,
				const wxString& titulo = wxT(""));
	~SubTitledPanelSinBorder();
};


class EXTAPI SubTitledPanelSeparatorV: public wxPanel {
public:
	SubTitledPanelSeparatorV(wxWindow *parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTAB_TRAVERSAL | wxNO_BORDER);
	~SubTitledPanelSeparatorV();

protected:
	int m_separacion;
};

class EXTAPI SubTitledPanelSeparatorH: public wxPanel {
public:
	SubTitledPanelSeparatorH(wxWindow *parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTAB_TRAVERSAL | wxNO_BORDER);
	~SubTitledPanelSeparatorH();

protected:
	int m_separacion;
};

class EXTAPI GinkgoBoxPanel: public wxPanel {
public:
	GinkgoBoxPanel(wxWindow *parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTAB_TRAVERSAL | wxNO_BORDER);
	~GinkgoBoxPanel();
protected:

	virtual void OnPaint(wxPaintEvent &event);

	wxColour m_backgroudColor;
	wxColour m_borderColor;
};


class EXTAPI GinkgoGauge: public wxPanel {
public:
	typedef enum {
		TCS_BLUE,
		TCS_RED,
		TCS_GREY,
		TCS_GREEN
	} TColorSchema;

	GinkgoGauge(wxWindow *parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTAB_TRAVERSAL | wxNO_BORDER);
	~GinkgoGauge();
	
	virtual void SetStatus(const wxString& status);
	virtual wxString GetStatus();
	virtual void SetProgress(float progress);
	virtual float GetProgress();

	virtual void SetMinSize(const wxSize &minSize);
	virtual void SetSize(const wxSize &minSize);
	
	virtual void SetColorSchema(TColorSchema schema);

protected:

	virtual void OnPaint(wxPaintEvent &event);
	virtual void OnEraseBackground( wxEraseEvent& event );
	virtual void OnSize(wxSizeEvent& event);
	virtual bool RecreateBuffer(const wxSize& size = wxDefaultSize);


	wxString m_status;
	float m_progress;
	int m_maxSizeOfText;

	/// Buffer bitmap
   wxBitmap                m_bufferBitmap;
	wxColour						m_fontColour;
	wxColour						m_startColour;
	wxColour						m_endColour;
	wxColour						m_borderColour;
};


