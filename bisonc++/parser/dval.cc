#include "parser.ih"

    // $$
bool Parser::dval(int nElements, Block &block, AtDollar const &atd)
{
    return dvalReplace(block, atd, "");
}