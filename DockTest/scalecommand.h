#ifndef SCALECOMMAND_H
#define SCALECOMMAND_H

#include <QUndoCommand>

class ScaleCommand : public QUndoCommand
{
public:
    enum {  Id = 1234 };
    ScaleCommand(const QPointF &oldSca,QUndoCommand *parent);

    void undo() override;
    void redo() override;
  //  bool mergeWith(const QUndoCommand *command) override;
   // int id() override{ return Id;}
private:
    //Entity item
    QPointF oldScale;
    QPointF newScale;
};

#endif // SCALECOMMAND_H
