#ifndef QSTRING_TYPECASTER_H
#define QSTRING_TYPECASTER_H

#include <pybind11/embed.h>
#include <QString>

namespace py = pybind11;

namespace pybind11 {
namespace detail {
  template <> struct type_caster<QString> {
    PYBIND11_TYPE_CASTER(QString, _("QString"));
    private:
        using qstr_caster_t = make_caster<std::string>;
        qstr_caster_t str_caster;

    public:
        bool load(handle src, bool convert) {
            if (str_caster.load(src, convert)) {
                value = QString::fromStdString(str_caster);
                return true;
            }

            return false;
        }

        static handle cast(const QString &qstring, return_value_policy policy, handle parent) {
            return qstr_caster_t::cast(qstring.toStdString(), policy, parent);
        }
    };
}}

#endif // QSTRING_TYPECASTER_H
