#ifndef MEOW_UTILS_EXPORTING_QUERY_DATA_EXPORT_FORMAT_SQL_REPLACES_H
#define MEOW_UTILS_EXPORTING_QUERY_DATA_EXPORT_FORMAT_SQL_REPLACES_H

#include "format.h"

namespace meow {
namespace utils {
namespace exporting {

class QueryDataExportFormatSQLReplaces : public QueryDataExportFormat
{
public:

    virtual QString id() const override {
        return "sql_replaces";
    }

    virtual QString name() const override {
        return QObject::tr("SQL REPLACEs");
    }

    virtual QString fileExtension() const override {
        return "sql";
    }
};


} // namespace exporting
} // namespace utils
} // namespace meow

#endif // MEOW_UTILS_EXPORTING_QUERY_DATA_EXPORT_FORMAT_SQL_REPLACES_H

