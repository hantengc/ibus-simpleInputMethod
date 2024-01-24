#include <glib.h>
#include <glib-object.h>
#include <glib/gstdio.h>

#include <ibus.h>

#include "module.h"

struct IBusModuleEngineClass
{
    IBusEngineClass parent;
};

static IBusEngineClass *parent_class = NULL;
static SimpleIMForIBus *module_ = nullptr;

static void ibus_simpleim_engine_class_init(IBusModuleEngineClass *);
static void ibus_simpleim_engine_init(IBusEngine *engine);
static void ibus_simpleim_engine_destroy(IBusEngine *engine);
static gboolean ibus_simpleim_engine_process_key_event(IBusEngine *engine,
                                                       guint keyval,
                                                       guint keycode,
                                                       guint modifiers);
static void ibus_simpleim_engine_focus_in(IBusEngine *engine);
static void ibus_simpleim_engine_focus_out(IBusEngine *engine);
static void ibus_simpleim_engine_reset(IBusEngine *engine);
static void ibus_simpleim_engine_enable(IBusEngine *engine);
static void ibus_simpleim_engine_disable(IBusEngine *engine);

static void ibus_simpleim_engine_page_up(IBusEngine *engine);
static void ibus_simpleim_engine_page_down(IBusEngine *engine);
static void ibus_simpleim_engine_cursor_up(IBusEngine *engine);
static void ibus_simpleim_engine_cursor_down(IBusEngine *engine);
static void ibus_simpleim_engine_property_activate(IBusEngine *engine,
                                                   const gchar *prop_name,
                                                   guint prop_state);
static void ibus_simpleim_engine_candidate_clicked(IBusEngine *engine,
                                                   guint index,
                                                   guint button,
                                                   guint state);

static GType ibus_simpleim_engine_get_type()
{
    static GType type = 0;
    static const GTypeInfo type_info = {
        sizeof(IBusModuleEngineClass),
        (GBaseInitFunc)NULL,
        (GBaseFinalizeFunc)NULL,
        (GClassInitFunc)ibus_simpleim_engine_class_init,
        NULL,
        NULL,
        sizeof(SimpleIMForIBus),
        0,
        (GInstanceInitFunc)ibus_simpleim_engine_init,
    };

    if (type == 0)
    {
        type = g_type_register_static(IBUS_TYPE_ENGINE,
                                      "SimpleIMForIBus",
                                      &type_info,
                                      (GTypeFlags)0);
    }

    return type;
}

static void ibus_simpleim_engine_class_init(IBusModuleEngineClass *klass)
{
    ibus_warning("func = %s  line = %d\n", __FUNCTION__, __LINE__);
    IBusObjectClass *ibus_object_class = IBUS_OBJECT_CLASS(klass);
    IBusEngineClass *engine_class = IBUS_ENGINE_CLASS(klass);

    parent_class = (IBusEngineClass *)g_type_class_peek_parent(klass);

    ibus_object_class->destroy = (IBusObjectDestroyFunc)ibus_simpleim_engine_destroy;

    engine_class->process_key_event = ibus_simpleim_engine_process_key_event;
    engine_class->focus_in = ibus_simpleim_engine_focus_in;
    engine_class->focus_out = ibus_simpleim_engine_focus_out;
    engine_class->reset = ibus_simpleim_engine_reset;
    engine_class->enable = ibus_simpleim_engine_enable;
    engine_class->disable = ibus_simpleim_engine_disable;
    engine_class->page_up = ibus_simpleim_engine_page_up;
    engine_class->page_down = ibus_simpleim_engine_page_down;
    engine_class->cursor_up = ibus_simpleim_engine_cursor_up;
    engine_class->cursor_down = ibus_simpleim_engine_cursor_down;
    engine_class->property_activate = ibus_simpleim_engine_property_activate;
    engine_class->candidate_clicked = ibus_simpleim_engine_candidate_clicked;
}

static void ibus_simpleim_engine_init(IBusEngine *engine)
{
    ibus_warning("func = %s  line = %d\n", __FUNCTION__, __LINE__);
    module_ = new SimpleIMForIBus(engine);
}

static void ibus_simpleim_engine_destroy(IBusEngine *engine)
{
    ibus_warning("func = %s  line = %d\n", __FUNCTION__, __LINE__);
    delete module_;
}

static gboolean ibus_simpleim_engine_process_key_event(IBusEngine *engine,
                                                       guint keyval,
                                                       guint keycode,
                                                       guint modifiers)
{
    module_->keyEvent(engine, keyval, keycode, modifiers);
    return false;
}

static void ibus_simpleim_engine_reset(IBusEngine *engine)
{
    module_->reset(engine);
}

static void ibus_simpleim_engine_enable(IBusEngine *engine)
{
    module_->activate(engine);
}

static void ibus_simpleim_engine_disable(IBusEngine *engine)
{
    module_->deactivate(engine);
}

static void ibus_simpleim_engine_focus_in(IBusEngine *engine)
{
    ibus_warning("func = %s  line = %d\n", __FUNCTION__, __LINE__);
}
static void ibus_simpleim_engine_focus_out(IBusEngine *engine)
{
    ibus_warning("func = %s  line = %d\n", __FUNCTION__, __LINE__);
}

static void ibus_simpleim_engine_page_up(IBusEngine *engine)
{
    (void)(engine);
}

static void ibus_simpleim_engine_page_down(IBusEngine *engine)
{
    (void)(engine);
}

static void ibus_simpleim_engine_cursor_up(IBusEngine *engine)
{
    (void)(engine);
}

static void ibus_simpleim_engine_cursor_down(IBusEngine *engine)
{
    (void)(engine);
}

static void ibus_simpleim_engine_property_activate(IBusEngine *engine,
                                                   const gchar *prop_name,
                                                   guint prop_state)
{
    (void)(engine);
    (void)(prop_name);
    (void)(prop_state);
}

static void ibus_simpleim_engine_candidate_clicked(IBusEngine *engine,
                                                   guint index,
                                                   guint button,
                                                   guint state)
{
    (void)(engine);
    (void)(index);
    (void)(button);
    (void)(state);
}

class ConnectToIBus
{
public:
    ConnectToIBus()
    {
        init_with_ibus();
        init_with_factory();
    }

    ~ConnectToIBus()
    {
        g_object_unref(bus_);
        g_object_unref(factory_);
    }

    void exec()
    {
        ibus_main();
    }

private:
    void init_with_ibus()
    {
        ibus_init();
        bus_ = ibus_bus_new();

        if (!ibus_bus_is_connected(bus_))
        {
            ibus_warning("ibus bus is not connect!");
            exit(0);
        }

        g_signal_connect(bus_, "disconnected", G_CALLBACK(ibus_disconnect_cb), NULL);
    }

    void init_with_factory()
    {
        GType type = ibus_simpleim_engine_get_type();
        if (type == G_TYPE_INVALID)
        {
            ibus_warning("Can not create engine type!\n");
            exit(1);
        }

        factory_ = ibus_factory_new(ibus_bus_get_connection(bus_));

        ibus_factory_add_engine(factory_, "SimpleInputMethod", type);
        if (!ibus_bus_request_name(bus_, "com.simple.InputMethod", 0))
        {
            ibus_warning("error requesting bus name!");
        }
    }

    static void ibus_disconnect_cb()
    {
        ibus_warning("bus disconnected\n");
        ibus_quit();
    }

private:
    IBusBus *bus_ = nullptr;
    IBusComponent *component = nullptr;
    IBusFactory *factory_ = nullptr;
};

int main(int argc, char **argv)
{
    ibus_warning("ibus - simpleim input method.\n");
    ConnectToIBus connectToIBus;
    connectToIBus.exec();
    return 0;
}