#include "TestUpdate.h"
#include "DataBaseQuery.h"
#include "DataBaseUpdater.h"
#include "TaskHelpUtils.h"

void TestUpdate::doTest() {
    // change id = 1 case
    auto all = DataBaseQuery::all();

    for (auto& each : all) {
        if (each->gain_id() == 2) {
            each->setgroupName("Study!");
            each->setdescription("Welp! already update");
            if (!DataBaseUpdater::updateTargetTask(*each)) {
                qDebug() << "Update failed!";
            }
        }
    }

    for (auto& each : all) {
        delete each;
    }

    all = DataBaseQuery::all();

    for (auto& each : all) {
        TaskHelpUtils::display_as_format(*each);
        delete each;
    }
}
