#include <LSound_Registration.h>

#include <Sound_Engine.h>
#include <Sound_Data.h>
#include <Sound.h>

using namespace LSound;


void LSound::register_types(LV::Object_Constructor& _object_constructor,
                            const LST::Function<const LEti::Resources_Manager*()>& _resources_manager_getter)
{
    L_ASSERT(_resources_manager_getter);

    Sound_Engine::instance();   //  initialization

    _object_constructor.register_type<LSound::Sound_Data_Stub>();

    _object_constructor.register_type<LSound::Sound_Stub>().override_initialization_func([_resources_manager_getter](LV::Variable_Base* _product)
    {
        LSound::Sound_Stub* product = (LSound::Sound_Stub*)_product;

        product->resources_manager = _resources_manager_getter();
    });
}
