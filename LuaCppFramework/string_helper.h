
#pragma once

#include <vector>
#include <functional>
#include <algorithm>
#include <locale>

namespace crt
{
	template< typename char_t >
	struct is_space_functor : public std::unary_function< char_t, char_t >
	{
		is_space_functor(const std::locale& loc)
		: loc_(loc)
		{
		}

		is_space_functor&	operator=(const is_space_functor& other)
		{
			loc_ = other.loc_;
		}

		bool	operator()(char_t ch)	const
		{
			return std::isspace(ch, loc_);
		}

	private:

		const std::locale&	loc_;

	};

	template< typename char_t >
	struct to_lower_functor : public std::unary_function< char_t, char_t >
	{
		to_lower_functor(const std::locale& loc)
		: loc_(loc)
		{
		}

		to_lower_functor&	operator=(const to_lower_functor& other)
		{
			loc_ = other.loc_;
		}

		char_t	operator()(char_t ch)	const
		{
			return std::tolower< char_t >(ch, loc_);
		}

	private:

		const std::locale&	loc_;

	};

	template< typename char_t >
	struct to_upper_functor : public std::unary_function< char_t, char_t >
	{
		to_upper_functor(const std::locale& loc)
		: loc_(loc)
		{
		}

		to_upper_functor&	operator=(const to_upper_functor& other)
		{
			loc_ = other.loc_;
		}

		char_t	operator()(char_t ch)	const
		{
			return std::toupper< char_t >(ch, loc_);
		}

	private:

		const std::locale&	loc_;

	};

	template< class string_t >
	string_t	trim_left(const string_t& str, const std::locale& loc = std::locale())
	{
		string_t::const_iterator pos = std::find_if(str.begin(), str.end(), std::not1(is_space_functor< string_t::value_type >(loc)));
		return str.substr(std::distance(str.begin(), pos));
	}
	template< class string_t >
	string_t	trim_right(const string_t& str, const std::locale& loc = std::locale())
	{
		string_t::const_iterator pos = std::find_if(str.rbegin(), str.rend(), std::not1(is_space_functor< string_t::value_type >(loc))).base();
		return str.substr(0, std::distance(str.begin(), pos));
	}
	template< class string_t >
	string_t	trim(const string_t& str, const std::locale& loc = std::locale())
	{
		return trim_left(trim_right(str, loc), loc);
	}

	template< class string_t >
	string_t	trim_left(const string_t& str, const string_t& drops)
	{
		string_t::size_type pos = str.find_first_not_of(drops);
		if (pos == string_t::npos)
		{
			pos = str.size();
		}

		return str.substr(pos);
	}
	template< class string_t >
	string_t	trim_right(const string_t& str, const string_t& drops)
	{
		string_t::size_type pos = str.find_last_not_of(drops);
		return str.substr(0, pos + 1);
	}
	template< class string_t >
	string_t	trim(const string_t& str, const string_t& drops)
	{
		return trim_left(trim_right(str, drops), drops);
	}
	template< class string_t >
	string_t	trim(const string_t& str, const typename string_t::value_type* drops)
	{
		return trim(str, string_t(drops));
	}

	template< class string_t >
	string_t	to_lower(string_t str, const std::locale& loc = std::locale())
	{
		std::transform(str.begin(), str.end(), str.begin(), to_lower_functor< string_t::value_type >(loc));
		return str;
	}
	template< class string_t >
	string_t	to_upper(string_t str, const std::locale& loc = std::locale())
	{
		std::transform(str.begin(), str.end(), str.begin(), to_upper_functor< string_t::value_type >(loc));
		return str;
	}

	template< class string_t >
	void	split(const string_t& input, std::vector< string_t >& tokens, const string_t& delimiters)
	{
		string_t::size_type pre_pos = 0;
		string_t::size_type next_pos = 0;
		while (next_pos != string_t::npos)
		{
			next_pos = input.find_first_of(delimiters, pre_pos);

			tokens.push_back(
				input.substr(
				pre_pos,
				(next_pos == string_t::npos) ? next_pos : (next_pos - (pre_pos))
				)
				);

			pre_pos = next_pos + 1;
		}
	}

	template< class string_t >
	void	trim_left(string_t* str, const std::locale& loc = std::locale())
	{
		str->erase(str->begin(), std::find_if(str->begin(), str->end(), std::not1(is_space_functor< string_t::value_type >(loc))));
	}
	template< class string_t >
	void	trim_right(string_t* str, const std::locale& loc = std::locale())
	{
		str->erase(std::find_if(str->rbegin(), str->rend(), std::not1(is_space_functor< string_t::value_type >(loc))).base(), str->end());
	}
	template< class string_t >
	void	trim(string_t* str, const std::locale& loc = std::locale())
	{
		trim_right(str, loc);
		trim_left(str, loc);
	}

	template< class string_t >
	void	to_lower(string_t* str, const std::locale& loc = std::locale())
	{
		std::transform(str->begin(), str->end(), str->begin(), to_lower_functor< string_t::value_type >(loc));
	}
	template< class string_t >
	void	to_upper(string_t* str, const std::locale& loc = std::locale())
	{
		std::transform(str->begin(), str->end(), str->begin(), to_upper_functor< string_t::value_type >(loc));
	}

	template< class string_t >
	void	split(const string_t& input, std::vector< string_t >& tokens, const typename string_t::value_type* delimiters)
	{
		split(input, tokens, string_t(delimiters));
	}

	template< class string_t >
	void	replace(string_t& str, const string_t& from, const string_t& to)
	{
		string_t::size_type here = 0;
		string_t::size_type found = 0;
		while ((found = str.find(from, here)) != string_t::npos)
		{
			str.replace(found, from.size(), to);
			here = found + to.size();
		}
	}

	template< class string_t >
	void	replace(string_t& str, const typename string_t::value_type* from, const typename string_t::value_type* to)
	{
		replace(str, string_t(from), string_t(to));
	}

};