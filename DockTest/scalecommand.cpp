#include "scalecommand.h"
ScaleCommand::ScaleCommand(const QPointF &oldSca,QUndoCommand *parent): QUndoCommand(parent)
{
    oldScale = oldSca;
}
ScaleCommand::undo()
{

}
ScaleCommand::redo()
{

}
