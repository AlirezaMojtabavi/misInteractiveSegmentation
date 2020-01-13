#ifndef TGT_EXCEPTION
#define TGT_EXCEPTION

#include "misCommonHeader.h"

/*
    Note: Use std::bad_alloc for out of memory error
*/

/**
 * Base class for all exceptions.
 */

class MISCOMMONEXPORT misException : public std::exception {
public:
    misException(const std::string& what = "") ;
    virtual ~misException() throw() {}

    virtual const char* what() const throw();
protected:
    std::string what_;
};

//

/**
 * Base class for all file based exceptions.
 */
class MISCOMMONEXPORT FileException : public misException {
public:
    /// @param filename The name of the affected file.
    FileException(const std::string& what = "", const std::string filename = "")
        : misException(what), filename_(filename) {}
    virtual ~FileException() throw() {}

    /// Returns the name of the affected file.
    const std::string& getFileName() const throw() { return filename_; }

protected:
    std::string getErrorMessage(const std::string& exception, const std::string& what,
                                const std::string& filename) const throw();

    std::string filename_;
};

//

/**
 * Thrown when a file was not found.
 */
class MISCOMMONEXPORT FileNotFoundException : public FileException {
public:
    /// @param filename The name of the file which was not found.
    FileNotFoundException(const std::string& what = "", const std::string& filename = "");
    virtual ~FileNotFoundException() throw() {}
};

//

/**
 * Thrown when a file couldn't be opened. No proper permessions may be the cause
 * for example.
 */
class MISCOMMONEXPORT FileAccessException : public FileException {
public:
    /// @param filename The name of the file which couldn't be opened.
    FileAccessException(const std::string& what = "", const std::string& filename = "");
    virtual ~FileAccessException() throw() {}
};

//

/**
 * Thrown when a file was tried to load but file/format of the file is
 * corrupted.
 */
class MISCOMMONEXPORT CorruptedFileException : public FileException {
public:
    CorruptedFileException(const std::string& what = "", const std::string& filename = "");
    virtual ~CorruptedFileException() throw() {}
};

//

/**
 * Thrown when a file was tried to load or save in an unsupported format.
 */
class MISCOMMONEXPORT UnsupportedFormatException : public FileException {
public:
    /// @param extension The extension which is not supported.
    UnsupportedFormatException(const std::string& extension, const std::string& filename = "");
    virtual ~UnsupportedFormatException() throw() {}
};

//

/**
 * Thrown when an i/o operation could not be completed successfull. The cause
 * may be a full or damaged disk for instance. Furthermore this misException is
 * thrown when no special error information is available when dealing with i/o
 * operations. This is the case when using fstream for instance.
 */
class MISCOMMONEXPORT IOException : public FileException {
public:
    IOException(const std::string& what = "", const std::string& filename = "");
    virtual ~IOException() throw() {}
};

//

#endif // TGT_EXCEPTION
