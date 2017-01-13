#ifndef SRC_CONFIGEDITOR_H_
#define SRC_CONFIGEDITOR_H_

#include <string>
#include <WPILib.h>

enum ConfigType
{
    CONFIG_INT,
    CONFIG_FLOAT,
    CONFIG_DOUBLE,
    CONFIG_STRING
};

class ConfigEditor
{
public:
    ConfigEditor(void);
    ~ConfigEditor(void);
    void update(void);

    void saveConfig(void);
    void getConfig(void);
    void showAllKeys(void);

    int getInt(std::string key, int defaultValue = 0);
    float getFloat(std::string key, float defaultValue = 0.0f);
    double getDouble(std::string key, double defaultValue = 0.0);
    std::string getString(std::string key, std::string defaultValue = "");

    void putProgDouble(std::string key, double value);
private:
    struct ConfigVariable
    {
	std::string name;
	ConfigType type;
    };

    static const ConfigVariable m_keys[];
    static const int m_keysLength;
    static Preferences *m_preferences;
};

#endif /* SRC_CONFIGEDITOR_H_ */
