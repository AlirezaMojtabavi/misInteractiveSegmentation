#pragma once
#include <string>
#include <map>
#include <list>

#include <api/api.h>
#include <api/iexception.h>
#include <api/dicom/dicomdataset.h>

namespace GIL {
	namespace DICOM {
		class IDICOMImg2DCM;
		class IDICOMManager;
	}
}

class DcmElement;

namespace GIL {
	namespace DICOM {

		class IDICOMImg2DCM;
		class IDICOMManager;

		class EXTAPI TipoTagPrivado {
		public:
			TipoTagPrivado() {}
			virtual ~TipoTagPrivado() {}
			virtual std::string ToString() = 0;
			virtual DcmElement* ToElement(unsigned int group, unsigned int element) = 0;
		};

		class EXTAPI TagPrivadoString: public TipoTagPrivado {
		public:
			TagPrivadoString(const std::string& valor)
			{
				Valor = valor;
			}
			virtual ~TagPrivadoString() {}

			virtual std::string ToString() {
				return Valor;
			}

			virtual DcmElement* ToElement(unsigned int group, unsigned int element);
		protected:
			std::string Valor;
		};


		class EXTAPI TagPrivadoUndefined: public TipoTagPrivado {
		public:
			TagPrivadoUndefined();

			TagPrivadoUndefined(unsigned int size);

			TagPrivadoUndefined(unsigned char* valor, unsigned int size);

			virtual ~TagPrivadoUndefined();

			TagPrivadoUndefined(const TagPrivadoUndefined& otro);

			TagPrivadoUndefined& operator = (const TagPrivadoUndefined& otro) ;

			void Copiar(void* ptrCopia, int size) ;

			virtual std::string ToString() ;

			unsigned char* GetValor();

			unsigned int GetSize();

			virtual DcmElement* ToElement(unsigned int group, unsigned int element);
		protected:
			unsigned char* Valor;
			unsigned int Size;
		};

		class EXTAPI TipoPrivateTags {
		public:
			typedef std::map<unsigned char, TipoTagPrivado* > ListaTags;
			std::string UIDModulo;

			TipoPrivateTags(){

			}

			TipoPrivateTags(const std::string& uidModulo){
				this->UIDModulo = uidModulo;
			}

			~TipoPrivateTags() {
				Vaciar();
			}

			ListaTags& GetListaTags()
			{
				return Tags;
			}

			void Vaciar()
			{
				for(ListaTags::iterator it=Tags.begin(); it!=Tags.end(); ++it){
					if((*it).second!=NULL){
						delete ((*it).second);
					}
				}
				Tags.clear();
			}

			void DeleteTag(unsigned char tag){
				if(Tags.find(tag)!=Tags.end()){
					//se borra
					if (Tags[tag] != NULL) {
						delete Tags[tag];
					}
					Tags.erase(tag);
				}
			}

			bool GetTag(unsigned char tag, std::string& valor) {
				if(Tags.find(tag)!=Tags.end()){
					valor = Tags[tag]->ToString();
					return true;
				} else {
					valor="";
					return false;
				}
			}

			TagPrivadoUndefined* GetTagUndefined(unsigned char tag)
			{
				if(Tags.find(tag)!=Tags.end()){
					TagPrivadoUndefined* pTag = dynamic_cast<TagPrivadoUndefined*> (Tags[tag]);
					return pTag;
				} else {
					return NULL;
				}				
			}

			void SetTag(unsigned char tag, const std::string& valor){
				if(Tags.find(tag) != Tags.end()) {
					delete Tags[tag];
				}
				Tags[tag] = new TagPrivadoString(valor);
			}

			void SetTag(unsigned char tag, unsigned char* valor, int longitud) {
				if(Tags.find(tag) != Tags.end()) {
					delete Tags[tag];
				}
				Tags[tag] = new TagPrivadoUndefined(valor, longitud);
			}

			TagPrivadoUndefined* NewTagUndefined(unsigned char tag, int longitud) {
				if(Tags.find(tag) != Tags.end()) {
					delete Tags[tag];
				}
				TagPrivadoUndefined* pTag = new TagPrivadoUndefined(longitud);
				Tags[tag] = pTag;
				return pTag;
			}
		protected:			
			ListaTags Tags;

		};
		
		class EXTAPI TipoMetaInfo {
		public:
			typedef std::map<std::string, std::string> ListaTags;
			
			ListaTags tags;
			
			~TipoMetaInfo()
			{
			}
			
			/* Obtiene un tag y lo asigna en el parámetro de salida valor.
			 Devuelve true si el tag existe y false si el tag no existe */
			bool getTag(const std::string& tag, std::string & valor)
			{
				ListaTags::iterator it = tags.find(tag);
				bool found = false;
				if (it != tags.end()) {
					valor = (*it).second;
					found = true;
				}
				return found;
			}
			
			std::string getTag(const std::string& tag)
			{
				ListaTags::iterator it = tags.find(tag);
				if (it != tags.end()) {
					return (*it).second;
				}
				return "";
			}
			
			template<class T> T getTagAs(const std::string& tag, const T& defaultValue)
			{
				T ret = defaultValue;
				std::stringstream is(getTag(tag));
				is >> ret;
				return ret;
			}
		};

		class EXTAPI I2DException : public GNC::GCS::IException {
		public:
			I2DException(const std::string& msg, const std::string& componente="GIL/I2D", bool fatal = true) throw() : GNC::GCS::IException(msg, componente, fatal)
			{
			}
			~I2DException() throw()
			{
			}			
		};
	}
}
