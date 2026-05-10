#include "Asset.h"
#include "Utils.h"

using namespace GFXEngine;

Asset::Asset(const std::string& name)
{
	m_name = name;
	m_uuid = Utils::generateUUID();
}