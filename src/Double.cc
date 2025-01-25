#include "Double.h"
#include <vector>

Double const & Double::print(std::ostream & ost) const 
{
	ost << *n_;
	return *this;
}

Double & Double::add(Object const & other) 
{
	auto cmp{dynamic_cast<Double const *>(&other)};
	if (nullptr == cmp)
		throw Object::exceptions::NOT_MATCHING_TYPES;

	*n_ += *(cmp->n_);
	return *this;
}

Double & Double::read(std::istream & ist) 
{
	ist >> *n_;
	return *this;
}

bool Double::equal(Object const & i) const noexcept(false) 
{
	auto cmp{dynamic_cast<Double const *>(&i)};
	if (nullptr == cmp)
		throw Object::exceptions::NOT_MATCHING_TYPES;

	return *n_ == *(cmp->n_);
}

int Double::compare(Object const & other) const noexcept(false) 
{
	auto cmp{dynamic_cast<Double const *>(&other)};
	if (nullptr == cmp)
		throw Object::exceptions::NOT_MATCHING_TYPES;

	auto diff{*n_ - *cmp->n_};
	return (diff > 0) ? 1 : (diff < 0) ? -1 : 0;
}

Double const & Double::save(std::FILE * src) const 
{
	if(!std::fwrite(&type_id_, sizeof(type_id_), 1, src))
		throw Object::exceptions::FWRITE_FAIL;
	if(!std::fwrite(n_, sizeof(*n_), 1, src))
		throw Object::exceptions::FWRITE_FAIL;
	return *this;
}

/*Чтение из переданного файла*/
Double & Double::read(std::FILE * src) 
{
	std::vector<std::byte> buf;
	buf.reserve(rwSize_());
	if(!fread(buf.data(), rwSize_(), 1, src))
		throw Object::exceptions::FREAD_FAIL;

	if (static_cast<char>(*buf.data()) != type_id_)
		throw Object::exceptions::NOT_MATCHING_TYPES;

	*n_ = *(double*)(buf.data() + 1);

	return *this;
}
