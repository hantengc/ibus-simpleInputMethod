#ifndef _MODULE_H_
#define _MODULE_H_

#include <ibus.h>

class SimpleModuleIMIBus : public IBusEngine
{
public:
    explicit SimpleModuleIMIBus(IBusEngine *engine = nullptr);
    virtual ~SimpleModuleIMIBus();
    void keyEvent(IBusEngine *engine, guint key_val, guint key_code, guint modifiers);
    void activate(IBusEngine *engine);
    void deactivate(IBusEngine *engine);
    void reset(IBusEngine *engine);

private:
    IBusEngine *engine_ = nullptr;
};
#endif