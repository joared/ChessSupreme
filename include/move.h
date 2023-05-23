#ifndef MOVE_H
#define MOVE_H

#include "bitboard.h"
#include "piece.h"

enum MoveType
{
    NORMAL,
    CAPTURE,
    DOUBLE_PUSH,
    EN_PASSANT
};

struct Move
{
    Move(Square from=-1, Square to=-1, MoveType mt=NORMAL) : from(from), to(to), moveType(mt) {};

    std::string toString();
    static Move fromString(std::string moveStr);
    bool isValid();

    void execute(Position* p);
    void undo(Position* p);

    template<MoveType mt = NORMAL>
    void execute(Position* p);
    template<MoveType mt = NORMAL>
    void undo(Position* p);

    Square from;
    Square to;
    MoveType moveType;
};

template <> void Move::execute<NORMAL>(Position* p);
template <> void Move::execute<DOUBLE_PUSH>(Position* p);
template <> void Move::execute<EN_PASSANT>(Position* p);

template <> void Move::undo<NORMAL>(Position* p);
template <> void Move::undo<DOUBLE_PUSH>(Position* p);
template <> void Move::undo<EN_PASSANT>(Position* p);

#endif /* MOVE_H */
