#include "String.h"
#include <vector>

int String::compare(Object const & other) const noexcept(false)
{
	auto cmp{dynamic_cast<String const *>(&other)};
	if (nullptr == cmp)
		throw Object::exceptions::NOT_MATCHING_TYPES;

	return str_.compare(cmp->str_);
}

String & String::add(Object const & other)
{
	auto cmp{dynamic_cast<String const *>(&other)};
	if (nullptr == cmp)
		throw Object::exceptions::NOT_MATCHING_TYPES;

	str_.append(cmp->str_);
	return *this;
}

/*Перезапись данного файла*/
String const & String::save(std::FILE * src) const
{
	// Запись типа объекта
	if (!std::fwrite(&type_id_, sizeof(type_id_), 1, src))
		throw Object::exceptions::FWRITE_FAIL;

	/*Запись длины строки*/
	auto len{str_.length()};
	if (!std::fwrite(&len, sizeof(str_.length()), 1, src))
		throw Object::exceptions::FWRITE_FAIL;

	/*Запись строки*/
	if (len > std::fwrite(str_.data(), sizeof(char), len, src))
		throw Object::exceptions::FWRITE_FAIL;

	return *this;
}

/*Чтение из переданного файла*/
String & String::read(std::FILE * src)
{
	/*Буфер для хранения прочитанного*/
	std::byte buf[std::max(sizeof(str_.length()), sizeof(type_id_))];

	/*Чтение типа объекта в буфер*/
	if (!fread(buf, sizeof(type_id_), 1, src))
		throw Object::exceptions::FREAD_FAIL;

	/*Если идентификатор типа из буфера не соответствует таковому для
	 *данного объекта, выбрасывается соответствующее исключение*/
	if (*(typeof type_id_ *)(buf) != type_id_)
		throw Object::exceptions::NOT_MATCHING_TYPES;

	/*Чтение длины строки*/
	if (!fread(buf, sizeof(str_.length()), 1, src))
		throw Object::exceptions::FREAD_FAIL;

	/*Выделение памяти под строку*/
	auto len{*(typeof str_.length() *)(buf)};
	str_.resize(len);

	/*Перезапись значения*/
	if (len > std::fread(str_.data(), sizeof(char), len, src))
		throw Object::exceptions::FREAD_FAIL;

	return *this;
}
