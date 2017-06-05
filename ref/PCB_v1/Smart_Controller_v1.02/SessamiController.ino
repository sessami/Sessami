#include "SessamiController.h"

void SessamiController::Background() {

}

void SessamiController::StateMachine() {
	if (rst)
		state = 0;
	switch (state) {
	//case 0 : ui.UIStateMachine(ui_rst);
	}
}
