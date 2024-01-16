#ifndef CONFIGMANAGEMENT_H
#define CONFIGMANAGEMENT_H

#include <iostream>
#include <QSettings>
#include <QApplication>
#include <QAtomicInt>
#include <atomic>
#include <mutex>

#define CONFIG_NAME "config.ini"
#define G_SYSTEM    "system"
class ConfigManagement
{
public:
    static ConfigManagement* GetSingleton() {
        static ConfigManagement* obj = nullptr;
        if (obj == nullptr) {
            obj = new ConfigManagement();
        }
        return obj;
    }

    QVariant GetValue(const std::string& group, const std::string& key, const QVariant& def = QVariant()) {
        QVariant var;
        obj->beginGroup(group.c_str());
        var = obj->value(key.c_str(), def);
        obj->endGroup();
        return var;
    }

    void SetValue(const std::string& group, const std::string& key, const QVariant& var) {
        obj->beginGroup(group.c_str());
        obj->setValue(key.c_str(), var);
        obj->endGroup();
        obj->sync();
    }

private:
    ConfigManagement() {
        obj = new QSettings(QApplication::applicationDirPath() + "/" + CONFIG_NAME, QSettings::IniFormat);
    };
    ~ConfigManagement() {
        if (obj != nullptr) {
            obj->sync();
            delete obj;
        }
    };
    ConfigManagement& operator=(const ConfigManagement&);

    QSettings *obj{};
};

#define GetCfgObj ConfigManagement::GetSingleton()
#define GetCfgValToBool(group,key) GetCfgObj->GetValue(group,key).toBool()
#define GetCfgValToBoolDef(group,key,def) GetCfgObj->GetValue(group,key,def).toBool()

#endif // CONFIGMANAGEMENT_H
