#include "module.h"

#include <glib.h>
#include <glib-object.h>
#include <glib/gstdio.h>

SimpleIMForIBus::SimpleIMForIBus(IBusEngine *engine) : engine_(engine) {}

SimpleIMForIBus::~SimpleIMForIBus() {}

void SimpleIMForIBus::keyEvent(IBusEngine *engine, guint key_val, guint key_code, guint modifiers)
{
    g_printf("func = %s  line = %d\n", __FUNCTION__, __LINE__);
}

void SimpleIMForIBus::activate(IBusEngine *engine)
{
    g_printf("func = %s  line = %d\n", __FUNCTION__, __LINE__);
}

void SimpleIMForIBus::deactivate(IBusEngine *engine)
{
    g_printf("func = %s  line = %d\n", __FUNCTION__, __LINE__);
}

void SimpleIMForIBus::reset(IBusEngine *engine)
{
    g_printf("func = %s  line = %d\n", __FUNCTION__, __LINE__);
}