#include "scalecommand.h"

ScaleCommand::ScaleCommand(const QPointF &oldSca,QUndoCommand *parent): QUndoCommand(parent)
{
    oldScale = oldSca;
}
void ScaleCommand::undo()
{

}
void ScaleCommand::redo()
{

}
