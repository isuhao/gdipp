#include "stdafx.h"
#include "font_config_criteria.h"
#include "gdipp_lib/helper.h"

namespace gdipp
{

font_config_criteria::font_config_criteria(const void *node)
	: _bold(-1),
	_italic(-1),
	_max_height(-1)
{
	if (node == NULL)
		return;

	const pugi::xml_node *node_ptr = reinterpret_cast<const pugi::xml_node *>(node);
	if (node_ptr->empty())
		return;

	pugi::xml_attribute attr;
	
	attr = node_ptr->attribute(L"bold");
	if (!attr.empty())
		wcs_convert(attr.value(), reinterpret_cast<short *>(&_bold));

	attr = node_ptr->attribute(L"italic");
	if (!attr.empty())
		wcs_convert(attr.value(), reinterpret_cast<short *>(&_italic));

	attr = node_ptr->attribute(L"max_height");
	if (!attr.empty())
		wcs_convert(attr.value(), &_max_height);

	attr = node_ptr->attribute(L"name");
	if (!attr.empty())
		_font_name = attr.value();
}

bool font_config_criteria::is_satisfied(bool bold, bool italic, LONG height, const wchar_t *font_name) const
{
	if (_bold >= 0 && (!_bold == bold))
		return false;

	if (_italic >= 0 && (!_italic == italic))
		return false;

	if (_max_height >= 0 && (_max_height < height))
		return false;

	if (!_font_name.empty())
	{
		const std::tr1::wregex font_name_regex(_font_name,
			std::tr1::regex_constants::icase | std::tr1::regex_constants::nosubs | std::tr1::regex_constants::optimize);
		return regex_match(font_name, font_name_regex);
	}

	return true;
}

}
