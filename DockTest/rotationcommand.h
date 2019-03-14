#ifndef ROTATIONCOMMAND_H
#define ROTATIONCOMMAND_H

#include <QUndoCommand>
#include <QPointF>

class RotationCommand : public QUndoCommand
{
public:
    enum {  Id = 1234 };
    RotationCommand(const QPointF &oldRot,QUndoCommand *parent);

    void undo() override;
    void redo() override;
    // bool mergeWith(const QUndoCommand *command) override;
    //int id() override{ return Id;}

private:
    //Entity item
    QPointF oldRotation;
    QPointF newRotation;
};

#endif // ROTATIONCOMMAND_H
