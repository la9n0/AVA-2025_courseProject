#pragma once

#define REGULAR_EXPRESSION 		9,   \
FST::NODE(1, FST::RELATION('a', 1)), \
FST::NODE(1, FST::RELATION('b', 2)), \
FST::NODE(5, FST::RELATION('b', 2), FST::RELATION('b', 6), FST::RELATION('c', 3), FST::RELATION('d', 3), FST::RELATION('e', 3)), \
FST::NODE(1, FST::RELATION('f', 4)), \
FST::NODE(1, FST::RELATION('b', 5)), \
FST::NODE(5, FST::RELATION('b', 5), FST::RELATION('b', 6), FST::RELATION('c', 3), FST::RELATION('d', 3), FST::RELATION('e', 3)), \
FST::NODE(2, FST::RELATION('b', 6), FST::RELATION('g', 7)), \
FST::NODE(1, FST::RELATION('f', 8)), \
FST::NODE()




#define MAX_LEN_CHAIN 100

namespace FST
{
	struct RELATION
	{
		char symbol;
		short nnode;
		RELATION(
			char c,
			short ns
		);
	};
	struct NODE
	{
		short n_relation;
		RELATION* relations;
		NODE();
		NODE(
			short n,
			RELATION rel, ...
		);
	};
	struct FST
	{
		const char* string;
		char lexema;
		short position;
		short nstates;
		NODE* nodes;
		short* rstates;
		FST(
			const char* s,
			const char lex,
			short ns,
			NODE n, ...
		);
	};

	bool step(FST& fst, short*& rstates);

	bool execute(
		FST& fst
	);

};
