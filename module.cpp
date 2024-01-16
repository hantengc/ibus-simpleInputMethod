#include "module.h"

#include <glib.h>
#include <glib-object.h>
#include <glib/gstdio.h>

SimpleModuleIMIBus::SimpleModuleIMIBus(IBusEngine *engine) : engine_(engine) {}

SimpleModuleIMIBus::~SimpleModuleIMIBus() {}

void SimpleModuleIMIBus::keyEvent(IBusEngine *engine, guint key_val, guint key_code, guint modifiers)
{
    g_printf("func = %s  line = %d\n", __FUNCTION__, __LINE__);
}

void SimpleModuleIMIBus::activate(IBusEngine *engine)
{
    g_printf("func = %s  line = %d\n", __FUNCTION__, __LINE__);
}

void SimpleModuleIMIBus::deactivate(IBusEngine *engine)
{
    g_printf("func = %s  line = %d\n", __FUNCTION__, __LINE__);
}

void SimpleModuleIMIBus::reset(IBusEngine *engine)
{
    g_printf("func = %s  line = %d\n", __FUNCTION__, __LINE__);
}