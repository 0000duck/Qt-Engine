#include "positioncommand.h"
PositionCommand::PositionCommand(const QPointF &oldPos,QUndoCommand *parent): QUndoCommand(parent)
{
    oldPosition = oldPos;
}
PositionCommand::undo()
{

}
PositionCommand::redo()
{

}
