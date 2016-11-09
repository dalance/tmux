/* $OpenBSD$ */

/*
 * Copyright (c) 2007 Nicholas Marriott <nicholas.marriott@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF MIND, USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <sys/types.h>

#include "tmux.h"

/*
 * Force set watermark of window.
 */

static enum cmd_retval	cmd_set_watermark_exec(struct cmd *, struct cmdq_item *);

const struct cmd_entry cmd_set_watermark_entry = {
	.name = "set-watermark",
	.alias = "setwm",

	.args = { "fs", 0, 0 },
	.usage = "[-fs]",

	.tflag = CMD_PANE,

	.flags = 0,
	.exec = cmd_set_watermark_exec
};

static enum cmd_retval
cmd_set_watermark_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args		*args = self->args;
	struct window_pane	*wp = item->state.tflag.wp;

    if (args_has(self->args, 'f')) {
	    window_pane_set_watermark(wp, READ_FAST_SIZE);
		cmdq_error(item, "set watermark to READ_FAST_SIZE");
    } else if (args_has(self->args, 's')) {
	    window_pane_set_watermark(wp, READ_SLOW_SIZE);
		cmdq_error(item, "set watermark to READ_SLOW_SIZE");
    } else {
		cmdq_error(item, "-f or -s must be given");
		return (CMD_RETURN_ERROR);
    }

	return (CMD_RETURN_NORMAL);
}