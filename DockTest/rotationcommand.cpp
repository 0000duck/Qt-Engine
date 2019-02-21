#include "rotationcommand.h"

RotationCommand::RotationCommand(const QPointF &oldRot,QUndoCommand *parent): QUndoCommand(parent)
{
    oldRotation = oldRot;
}

RotationCommand::undo()
{

}
RotationCommand::redo()
{

}
