#ifndef POSITIONCOMMAND_H
#define POSITIONCOMMAND_H

#include <QUndoCommand>
#include <QPointF>
class PositionCommand : public QUndoCommand
{
public:
    enum {  Id = 1234 };
    PositionCommand(const QPointF &oldPos,QUndoCommand *parent);

    void undo() override;
    void redo() override;
   // bool mergeWith(const QUndoCommand *command) override;
    //int id() override{ return Id;}
private:
    //Entity item
    QPointF oldPosition;
    QPointF newPosition;
};

#endif // POSITIONCOMMAND_H
