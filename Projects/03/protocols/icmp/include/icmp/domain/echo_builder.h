/*
 * echo_builder.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ECHO_BUILDER_H
#define ECHO_BUILDER_H

#include "echo.h"
#include "ptr_types.h"

class EchoBuilder {
	public:
		Echo build() {
			// TODO
			return Echo();
		}

		EchoPtr build_ptr() {
			// TODO
			return EchoPtr( new Echo() );
		}

	private:
		Echo variable_holder;
};

#endif /* !ECHO_BUILDER_H */

