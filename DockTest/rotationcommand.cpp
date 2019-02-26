#include "rotationcommand.h"

RotationCommand::RotationCommand(const QPointF &oldRot,QUndoCommand *parent): QUndoCommand(parent)
{
    oldRotation = oldRot;
}

void RotationCommand::undo()
{

}
void RotationCommand::redo()
{

}
