#include "ConfigEditor.h"

#include <iostream>
#include <sstream>

ConfigEditor::ConfigEditor()
{
    if (!m_preferences)
	m_preferences = Preferences::GetInstance();
    std::cout << "Initialized ConfigEditor" << std::endl;
}

/*
 * Static variable declarations
 */
const ConfigEditor::ConfigVariable ConfigEditor::m_keys[] =
{{"Example1",CONFIG_INT},
 {"Example2",CONFIG_FLOAT},
 {"Example3",CONFIG_DOUBLE},
 {"Example4",CONFIG_STRING}};

const int ConfigEditor::m_keysLength = sizeof(m_keys) / sizeof(ConfigEditor::ConfigVariable);

Preferences *ConfigEditor::m_preferences = 0;

ConfigEditor::~ConfigEditor()
{
}

/*
 * Sends requested variable's value to drive station.
 */
void ConfigEditor::getConfig()
{
    std::string keyName = SmartDashboard::GetString("Key Name", "");

    int pos = -1;
    for(int i = 0; i < m_keysLength; i++)
    {
        if(keyName == m_keys[i].name)
        {
            pos = i;
            break;
        }
    }

    if(pos == -1)
    {
        std::cout << "Key entered was not a valid variable" << std::endl;
        return;
    }

    ConfigType type = m_keys[pos].type;
    std::stringstream convert;

    switch (type)
    {
    case CONFIG_INT:
	convert << m_preferences->GetInt(keyName, 0);
	break;
    case CONFIG_FLOAT:
	convert << m_preferences->GetFloat(keyName, 0.0f);
	break;
    case CONFIG_DOUBLE:
	convert << m_preferences->GetDouble(keyName, 0.0);
	break;
    case CONFIG_STRING:
	convert << m_preferences->GetString(keyName, "");
	break;
    }
    SmartDashboard::PutString("Key Value", convert.str());
}

/*
 * Updates variable as dictated by drive station.
 */
void ConfigEditor::saveConfig()
{
    std::string keyName = SmartDashboard::GetString("Key Name", "");
    std::string newValue = SmartDashboard::GetString("New Value", "");

    int pos = -1;
    for(int i = 0; i < m_keysLength; i++)
    {
        if(keyName == m_keys[i].name)
        {
            pos = i;
            break;
        }
    }

    if(pos == -1)
    {
        std::cout << "Key entered was not a valid variable" << std::endl;
        return;
    }

    ConfigType type = m_keys[pos].type;
    std::stringstream convert(newValue);

    try
    {
	union
	{
	    int i;
	    float f;
	    double d;
	};

        switch (type)
	{
	case CONFIG_INT:
	    convert >> i;
	    m_preferences->PutInt(keyName, i);
	    break;
	case CONFIG_FLOAT:
	    convert >> f;
	    m_preferences->PutFloat(keyName, f);
	    break;
	case CONFIG_DOUBLE:
	    convert >> d;
	    m_preferences->PutDouble(keyName, d);
	    break;
	case CONFIG_STRING:
	    m_preferences->PutString(keyName, newValue);
	    break;
	}
    } catch (...)
    {
	std::cout << "Invalid value" << std::endl;
	return;
    }
}

/*
 * Outputs all of the keys to standard output
 * and SmartDashboard.
 */
void ConfigEditor::showAllKeys()
{
    std::cout << "Showing ConfigEditor keys" << std::endl;
    std::string final = "";
    for(int i = 0; i < m_keysLength; i++)
    {
	std::string type;
	switch (m_keys[i].type)
	{
	case CONFIG_INT:
	    type = "int";
	    break;
	case CONFIG_FLOAT:
	    type = "float";
	    break;
	case CONFIG_DOUBLE:
	    type = "double";
	    break;
	case CONFIG_STRING:
	    type = "string";
	    break;
	}
        final += m_keys[i].name+"\t"+type+"\n";
    }
    std::cout << final << std::endl;
    SmartDashboard::PutString("Keys",final);
}

/*
 * Updates input from variable editor. Should be
 * executed every cycle.
 */
void ConfigEditor::update()
{
    const char* buttons[2] = {"Get Value", "Set Value"};
    for (int i = 0; i < 1; i++)
    {
        if (SmartDashboard::GetBoolean(buttons[i], false))
        {
	    SmartDashboard::PutBoolean(buttons[i], false);
            std::cout << "Button " << buttons[i] << " was pressed" << std::endl;

            if(i == 0)
                getConfig();
            else if(i == 1)
                saveConfig();
        }
    }
}

/*
 * Gets the value of the specified key.
 */
int ConfigEditor::getInt(std::string key, int defaultValue)
{
    return m_preferences->GetInt(key, defaultValue);
}

float ConfigEditor::getFloat(std::string key, float defaultValue)
{
    return m_preferences->GetFloat(key, defaultValue);
}

double ConfigEditor::getDouble(std::string key, double defaultValue)
{
    return m_preferences->GetDouble(key, defaultValue);
}

std::string ConfigEditor::getString(std::string key, std::string defaultValue)
{
    return m_preferences->GetString(key, defaultValue);
}

/*
 * Saves a double value to the key.
 */
void ConfigEditor::putProgDouble(std::string key, double value)
{
    if(key.find("prog") == 0)
        m_preferences->PutDouble(key, value);
}
