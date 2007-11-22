#ifndef _INCLUDED_BLOCK_
#define _INCLUDED_BLOCK_

#include <iosfwd>
#include <vector>
#include <string>

class Block: public std::string
{
    size_t  d_line;
    std::string d_source;

    int     d_count;
    
    public:
        typedef std::pair<size_t, size_t> Range;

    private:
        std::vector<Range>  d_skip;     // skip these ranges when processing
                                        // a block: it contains the begin and
                                        // end positions of strings and quotes 
                                        // found inside the matched block
    public:
        Block();

        void clear();
                                        // clears the previous block contents
        void open(size_t lineno, std::string const &source);
        bool close();

        void saveDollar1(int offset);   // save $1 in $$ at the beginning
                                        // of a nested block

        void operator+=(char const *text);
  
        operator bool() const;          // return true if a block is active

        bool operator()(char const *text);  // add text if a block is active,
                                            // returning true if active

        std::vector<Range>::const_reverse_iterator skipRbegin() const;
        std::vector<Range>::const_reverse_iterator skipRend() const;
        size_t line() const;
        std::string const &source() const;
};

inline Block::Block()
:
    d_count(0)
{}

inline void Block::operator+=(char const *text)
{
    append(text);
}

inline Block::operator bool() const
{
    return d_count;
}

inline std::vector<Block::Range>::const_reverse_iterator 
Block::skipRbegin() const
{
    return d_skip.rbegin();
}
inline std::vector<Block::Range>::const_reverse_iterator 
Block::skipRend() const
{
    return d_skip.rend();
}
inline size_t Block::line() const
{
    return d_line;
}
inline std::string const &Block::source() const
{
    return d_source;
}

#endif

