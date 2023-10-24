/**
 *  AUTHOR:         Ondrej Nedojedly (https://www.github.com/ondranedo)
 *  DATE:           2023-10-10
 *  DESCRIPTION:    The main header file for the r8ge engine.
 *  LICENSE:        "../../LICENSE"
 *
 */

#ifndef R8GE_H
#define R8GE_H

#include "../r8ge-core/Core.h"
#include "../r8ge-core/Logger.h"
#include "../r8ge-core/instance/Instance.h"
#include "../r8ge-core/instance/GameInstance.h"
#include "../r8ge-core/instance/ConsoleAppInstance.h"
#include "../r8ge-core/fileio/File.h"
#include "../r8ge-core/fileio/fileReaders/Json.h"
#include "../r8ge-core/fileio/fileReaders/Binary.h"
#include "../r8ge-core/fileio/fileReaders/Text.h"
#include "../r8ge-core/fileio/fileReaders/Glsl.h"
#include "../r8ge-core/Ar8ge.h"
#include "../r8ge-core/events/Strokes.h"
#include "../r8ge-core/events/MouseEvents.h"
#include "../r8ge-core/events/WindowEvents.h"
#include "../r8ge-core/events/EventPayload.h"
#include "../r8ge-core/events/KeyEvents.h"
#include "../r8ge-core/events/Dispatcher.h"
#include "../r8ge-core/events/EngineEvents.h"
#include "../r8ge-core/Input.h"

#endif//!R8GE_H