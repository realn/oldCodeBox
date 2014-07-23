#pragma once

namespace CB{
	namespace IO{
		namespace File{
			enum class AccessType{
				ReadOnly,
				WriteOnly,
				ReadAndWrite,
			};
			enum class OpenAction{
				Open,			// Open, throw if not exists
				Create,			// Create empty, throw if exists
				AlwaysOpen,		// Open, if not exists - create empty
				AlwaysCreate	// Create, if exists - wipe and overwrite
			};
			enum class ShareType{
				None,
				ReadOnly,
				WriteOnly,
				ReadAndWrite
			};
		}
	}
}