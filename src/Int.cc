#include "Int.h"
#include <cstddef>
#include <vector>

Int & Int::operator=(Int const & i)
{
	*n_ = *i.n_;
	return *this;
}

Int const & Int::print(std::ostream & ost) const
{
	ost << *n_;
	return *this;
}

Int & Int::read(std::istream & ist)
{
	ist >> *n_;
	return *this;
}

int Int::compare(Object const & other) const noexcept(false)
{
	auto cmp{dynamic_cast<Int const *>(&other)};
	if (nullptr == cmp)
		throw Object::exceptions::NOT_MATCHING_TYPES;

	return static_cast<int>(*n_ - *cmp->n_);
}

Int & Int::add(Object const & other)
{
	auto cmp{dynamic_cast<Int const *>(&other)};
	if (nullptr == cmp)
		throw Object::exceptions::NOT_MATCHING_TYPES;

	*n_ += *(cmp->n_);
	return *this;
}

/*Перезапись данного файла*/
Int const & Int::save(std::FILE * src) const
{
	if (!std::fwrite(&type_id_, sizeof(type_id_), 1, src))
		throw Object::exceptions::FWRITE_FAIL;
	if (!std::fwrite(n_, sizeof(*n_), 1, src))
		throw Object::exceptions::FWRITE_FAIL;
	return *this;
}

/*Чтение из переданного файла*/
Int & Int::read(std::FILE * src)
{
	/*Буфер для хранения прочитанного*/
	std::vector<std::byte> buf;
	buf.reserve(rwSize_());

	/*Чтение файла в буфер*/
	if (!fread(buf.data(), rwSize_(), 1, src))
		throw Object::exceptions::FREAD_FAIL;

	/*Если идентификатор типа из буфера не соответствует таковому для
	 *данного объекта, выбрасывается соответствующее исключение*/
	if (static_cast<char>(*buf.data()) != type_id_)
		throw Object::exceptions::NOT_MATCHING_TYPES;

	/*Перезапись значения*/
	*n_ = *(int *)(buf.data() + 1);

	return *this;
}
