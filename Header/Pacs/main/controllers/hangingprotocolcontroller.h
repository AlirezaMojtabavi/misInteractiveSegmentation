/*
 *  
 *  $Id: hangingprotocolcontroller.h $
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
#include <string>
#include <map>
#include <list>
#include <api/autoptr.h>
#include <api/dicom/idicom.h>
class wxXmlNode;
class wxSizer;
class wxWindow;
class wxSizerItem;

namespace GNC {
	namespace GCS {
		class IVista;
		class Matcher;
		/**
		if series viewers implements this interface, getLayoutForSizer
		*/
		class IHangingSeriesViewer
		{
		public:
			virtual void getSeriesBase(GIL::DICOM::DicomDataset& seriesBase) = 0;
		};
		/**
		contract to realize layout...
		*/
		class IHangingProtocolContract 
		{
		public:
			virtual wxWindow* createSeriesSlot(const std::map<std::string, std::string>& properties, long pk = -1, const GNC::GCS::Ptr<GNC::GCS::Matcher>& pMatcher = NULL) = 0;
			virtual const std::list<long>& getOpeningSeries() = 0;
		};
		/**
		Class that evaluates study and series matching, depending on matching criteria over tags
		*/
		class Matcher
		{
		public:
			Matcher();
			/**
			Deserialize from xml
			*/
			Matcher(wxXmlNode* node);
			Matcher(const Matcher& other);
			~Matcher();
			bool MatchesStudy(long idStudy);
			bool MatchesSeries(long idSeries);
			/**
			serialize to XML
			*/
			wxXmlNode* serialize();
			/**
			getter and setter
			*/
			std::map<std::string, std::string>& getMatchingCriteria();
			void setMatchingCriteria(const std::map<std::string, std::string>& properties);
		protected:
			bool matches(const std::string& pathOfFile);
			std::map<std::string, std::string> matchingCriteria;
		};

		class HangingProtocol;
		/**
		Defines a specific layout, is recursive to allow splitted cells
		*/
		class Layout {
		public:
			Layout();
			/**
			deserialize from xml
			*/
			Layout(wxXmlNode* layoutRoot);
			Layout(const Layout& other);
			~Layout();
			/**
			Layout with a row and a column is a cell and cellList is empty
			*/
			bool isACell();
			/**
			serialize to XML
			*/
			wxXmlNode* serialize();

			void doLayout(IHangingProtocolContract* pContract, wxSizer* parentSizer);
			static GNC::GCS::Ptr<GNC::GCS::Layout> getLayoutFromSizer(wxSizer* pSizer);
		protected:
			static GNC::GCS::Ptr<GNC::GCS::Layout> getLayoutFromSizerItem(wxSizerItem* pSizerItem);
		public:

			/**
			getters and setters
			*/
			int getRows();
			void setRows(int rows);
			int getColumns();
			void setColumns(int columns);
			std::list<GNC::GCS::Ptr<Layout> >& getCellList();
			void setCellList(const std::list<GNC::GCS::Ptr<Layout> >& cellList);
			const GNC::GCS::Ptr<Matcher>& getMatcher();
			void setMatcher(const GNC::GCS::Ptr<Matcher>& matcher);
			std::map<std::string, std::string>& getProperties();
			void setProperties(const std::map<std::string, std::string>& properties);
			GNC::GCS::HangingProtocol* getParent();
			void setParent(GNC::GCS::HangingProtocol* pH);
			void setDefaultPosition();
			void setWindowProperties(bool isMaximized, int xPos, int yPos, int width, int height);
			void copyWindowProperties(const GNC::GCS::Layout& other);
			void applyWindowProperties(wxWindow* pWindow);
			void applyWindowProperties(GNC::GCS::IVista* pView);
		protected:
			int rows;
			int columns;
			/**
			pointer to parent
			*/
			GNC::GCS::HangingProtocol* pParent;
			/**
			left to right and top down list of cells
			*/
			std::list<GNC::GCS::Ptr<Layout> > cellList;
			/**
			if it's a cell series matching criteria
			*/
			GNC::GCS::Ptr<Matcher> seriesMatcher;
			/*
			here modules can insert key/value properies as zoom level, window/level...
			*/
			std::map<std::string, std::string> properties;
			/**
			if it's detached or not
			*/
			bool isDetached;
			/**
			Window details
			*/
			bool isMaximized;
			int xPos, yPos, width, height;
		};

		/**
		* window level setting
		*/
		class WindowLevelSetting 
		{
		public:
			WindowLevelSetting();
			WindowLevelSetting(double window, double level, const std::string& label);
			WindowLevelSetting(wxXmlNode* node);
			WindowLevelSetting(const WindowLevelSetting& other);
			~WindowLevelSetting();
			/**
			serialize to XML
			*/
			wxXmlNode* serialize();

			double getWindow() const;
			double getLevel() const;
			const std::string& getLabel() const;

			std::string toString() const;

			void setWindow(double window);
			void setLevel(double level);
			void setLabel(const std::string& label);
			
		protected:
			double window;
			double level;
			std::string label;
		};

		/**
		* default modality settings
		*/
		class DefaultModalitySettings 
		{
		public:
			typedef enum TInterpolationMode{
				TIM_NEAREST_NEIGHBOUR,
				TIM_LINEAR,
				TIM_CUBIC
			}TInterpolationMode;
			typedef std::list<GNC::GCS::Ptr<WindowLevelSetting> > TListOfWLSettings;
			DefaultModalitySettings();
			DefaultModalitySettings(wxXmlNode* node);
			DefaultModalitySettings(const DefaultModalitySettings& other);
			~DefaultModalitySettings();
			/**
			serialize to XML
			*/
			wxXmlNode* serialize();

			static std::string getDefaultWindowLevelLabel();
			static std::string getAutocalculateWindowLevelLabel();

			const TListOfWLSettings& getWLSettings() const;
			const std::string& getModality() const;
			const std::string& getInitialWindowLevelLabel() const;
			TInterpolationMode getInterpolationMode() const;

			void addWindowLevel(const GNC::GCS::Ptr<WindowLevelSetting>& wlSetting);
			void clearWindowLevels();
			void setModality(const std::string& modality);
			void setInitialWindowLevelLabel(const std::string& label);
			void setInterpolationMode(TInterpolationMode mode);
		protected:
			std::string modality;
			std::string initialWindowLevelLabel;
			TInterpolationMode interpolationMode;
			TListOfWLSettings listOfWLSettings;
		};

		/**
		HangingProtocol class, defines a hanging protocol
		*/
		class HangingProtocol {
		public:
			typedef std::list<GNC::GCS::Ptr<Layout> > TListOfLayouts;
			typedef std::map<std::string, GNC::GCS::Ptr<DefaultModalitySettings> > TMapOfModalitySettings;
			HangingProtocol();
			/**
			deserialize from xml
			*/
			HangingProtocol(wxXmlNode* node);
			HangingProtocol(const HangingProtocol& other);
			~HangingProtocol();
			void LoadDefaultModalitySettings();
			/**
			serialize to XML
			*/
			wxXmlNode* serialize();
			/**
			true if study matches with this hanging protocol
			*/
			bool matches(long idStudy);

			/**
			Getters and setters
			*/
			const std::string& getName();
			void setName(const std::string& name);
			const std::string& getDescription();
			void setDescription(const std::string& description);
			const std::string& getModuleSid();
			void setModuleSid(const std::string& name);
			int getOpeningMode();
			void setOpeningMode(int mode);
			const GNC::GCS::Ptr<Matcher>& getStudyMatcher();
			void setStudyMatcher(const GNC::GCS::Ptr<Matcher>& matcher);
			const TListOfLayouts& getLayouts();
			void addLayout(const GNC::GCS::Ptr<Layout>& layout);
			void clearLayouts();
			const TMapOfModalitySettings& getModalitySettingsMap();
			void addModalitySettings(const GNC::GCS::Ptr<DefaultModalitySettings>& settings);
			void clearModalitySettings();
			GNC::GCS::Ptr<DefaultModalitySettings> getModalitySettings(const std::string& modality);
			std::map<std::string, std::string>& getProperties();
			void setProperties(const std::map<std::string, std::string>& properties);
			bool isActive();
			void setActive(bool active);
		protected:
			/**
			Unique name
			*/
			std::string name;
			/**
			description
			*/
			std::string description;
			/**
			Module that opens this hanging protocol
			*/
			std::string moduleSid;
			/**opening mode
			*/
			int openingMode;
			/**
			study matching
			*/
			GNC::GCS::Ptr<Matcher> studyMatcher;
			/**
			layout of the protocol
			*/
			TListOfLayouts layouts;
			/**
			visualization modality settings
			*/
			TMapOfModalitySettings modalitySettings;
			/*
			here modules can insert key/value properies
			*/
			std::map<std::string, std::string> properties;
			/*
			if it's active
			*/
			bool active;
		};

		/**
		Hanging protocol controller class
		*/
		class HangingProtocolController 
		{
		public:
			/**
			Singleton method
			*/
			static HangingProtocolController* Instance();

			/**
			Free singleton
			*/
			static void FreeInstance();

			/**
			Get hanging protocol for specified study
			*/
			GNC::GCS::Ptr<HangingProtocol> GetProtocolForStudy(long idStudy);

			/**
			stores hanging protocol list
			*/
			void StoreHangingProtocolConfiguration();
			/**
			gets a copy of hanging protocols
			*/
			std::list<GNC::GCS::Ptr<HangingProtocol> > getHangingProtocols();
			/**
			sets hanging protocol list...
			*/
			void setHangingProtocols(std::list<GNC::GCS::Ptr<HangingProtocol> > listOfProtocols);
		protected:
			/**
			Creation method
			*/
			HangingProtocolController();

			/**
			Destruction method
			*/
			~HangingProtocolController();

			/**
			Load from configuration
			*/
			void LoadFromConfiguration();

			/**
			singleton attribute
			*/
			static HangingProtocolController* m_pInstance;

			/**
			protocol list
			*/
			std::list<GNC::GCS::Ptr<HangingProtocol> > listOfProtocols;
		};
	}
}
