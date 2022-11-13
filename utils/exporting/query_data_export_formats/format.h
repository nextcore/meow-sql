#ifndef MEOW_UTILS_EXPORTING_QUERY_DATA_EXPORT_FORMAT_H
#define MEOW_UTILS_EXPORTING_QUERY_DATA_EXPORT_FORMAT_H

#include <QString>
#include <QObject>
#include <QModelIndex>
#include <QMap>
#include <QSet>
#include <memory>

namespace meow {

namespace ui {
namespace models {
class BaseDataTableModel;
}
}

namespace utils {
namespace exporting {

class QueryDataExportFormat
{
public:

    enum class OptionsValue
    {
        FieldSeparator,
        Encloser,
        LineTerminator,
        NullValue
    };

    using OptionsValueMap = QMap<OptionsValue, QString>;
    using OptionsValueSet = QSet<OptionsValue>;

    enum class OptionsBool
    {
        IncludeColumnNames,
        IncludeAutoIncrementColumn,
        IncludeSQLQuery,
        RemoveLineBreaksFromContents
    };

    using OptionsBoolSet = QSet<OptionsBool>;

    void init() {
        _optionsValue = defaultOptionsValue();
        _optionsBool = defaultOptionsBool();
    }

    virtual ~QueryDataExportFormat() {}

    virtual QString id() const = 0;
    virtual QString name() const = 0;
    virtual QString fileExtension() const = 0;

    virtual QString header() const {
        return QString();
    }

    virtual QString row(int index) const { // TODO = 0
        Q_UNUSED(index);
        return QString();
    }

    virtual OptionsValueMap defaultOptionsValue() const {
        return {};
    }

    virtual OptionsValueSet editableOptionsValue() const {
        return {};
    }

    virtual OptionsBoolSet defaultOptionsBool() const {
        return {};
    }

    virtual OptionsBoolSet editableOptionsBool() const {
        return {};
    }

    QString fieldSeparator() const {
        return optionValue(OptionsValue::FieldSeparator);
    }
    QString encloser() const {
        return optionValue(OptionsValue::Encloser);
    }
    QString lineTerminator() const {
        return optionValue(OptionsValue::LineTerminator);
    }
    QString nullValue() const {
        return optionValue(OptionsValue::NullValue);
    }

    void setData(ui::models::BaseDataTableModel * model) {
        _model = model;
    }

    void setOptionValue(OptionsValue option, const QString & value) {
        _optionsValue[option] = value;
    }

    QString optionValue(OptionsValue option) const {
        return _optionsValue.value(option, QString());
    }

    void setOptionBool(OptionsBool option, bool value) {
        if (value) {
            _optionsBool.insert(option);
        } else {
            _optionsBool.remove(option);
        }
    }

    bool optionBool(OptionsBool option) const {
        return _optionsBool.contains(option);
    }

    void setSourceName(const QString name) {
        _sourceName = name;
    }
    QString sourceName() const {
        return _sourceName;
    }

protected:

    QString headerName(int col) const;
    QString data(int row, int col) const;
    bool isNull(int row, int col) const;
    bool isNumericDataType(int col) const;
    QString escapeEncloser(const QString & data,
                           const QString & encloser = QString()) const;
    QString removeLineBreaks(const QString & data) const;
    QString escHTML(const QString & str) const {
        return str.toHtmlEscaped();
    }

    bool isIncludeColumnNames() const {
        return optionBool(OptionsBool::IncludeColumnNames);
    }
    bool isIncludeAutoIncrementColumn() const {
        return optionBool(OptionsBool::IncludeAutoIncrementColumn);
    }
    bool isRemoveLineBreaksFromContents() const {
        return optionBool(OptionsBool::RemoveLineBreaksFromContents);
    }

    int nextVisibleColumn(int curIndex) const;

    ui::models::BaseDataTableModel * _model = nullptr;
    OptionsValueMap _optionsValue;
    OptionsBoolSet _optionsBool;
    QString _sourceName;
};

using QueryDataExportFormatPtr = std::shared_ptr<QueryDataExportFormat>;

inline uint qHash(const QueryDataExportFormat::OptionsValue& value)
{
    return static_cast<uint>(value);
}

inline uint qHash(const QueryDataExportFormat::OptionsBool& value)
{
    return static_cast<uint>(value);
}

} // namespace exporting
} // namespace utils
} // namespace meow

#endif // MEOW_UTILS_EXPORTING_QUERY_DATA_EXPORT_FORMAT_H
