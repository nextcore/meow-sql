#ifndef MEOW_UTILS_EXPORTING_QUERY_DATA_EXPORT_FORMAT_MARKDOWN_H
#define MEOW_UTILS_EXPORTING_QUERY_DATA_EXPORT_FORMAT_MARKDOWN_H

#include "format.h"

namespace meow {
namespace utils {
namespace exporting {

class QueryDataExportFormatMarkdown : public QueryDataExportFormat
{
public:

    virtual QString id() const override {
        return "markdown";
    }

    virtual QString name() const override {
        return QObject::tr("Markdown Here");
    }

    virtual QString fileExtension() const override {
        return "md";
    }
};


} // namespace exporting
} // namespace utils
} // namespace meow

#endif // MEOW_UTILS_EXPORTING_QUERY_DATA_EXPORT_FORMAT_MARKDOWN_H

