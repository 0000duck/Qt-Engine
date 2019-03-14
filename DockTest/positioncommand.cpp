#include "positioncommand.h"

PositionCommand::PositionCommand(const QPointF &oldPos,QUndoCommand *parent): QUndoCommand(parent)
{
    oldPosition = oldPos;
}

void PositionCommand::undo()
{

}

void PositionCommand::redo()
{

}
