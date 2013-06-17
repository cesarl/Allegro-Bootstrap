#ifndef					__STR_UTIL_HPP__
# define				__STR_UTIL_HPP__

#include				<string>
#include				<vector>
#include				<algorithm>

inline void				split(const std::string &str,
					      std::vector<std::string> &tokens,
					      const std::string &regex = " \t\n")
{
  tokens.clear();

  for (std::string::size_type p1 = 0, p2 = 0; p1 != std::string::npos; )
    {
      p1 = str.find_first_not_of(regex, p1);
      if (p1 != std::string::npos)
	{
	  p2 = str.find_first_of(regex, p1);
	  tokens.push_back(str.substr(p1, p2 - p1));
	  p1 = p2;
	}
    }
}

#endif					// __STR_UTIL_HPP__
