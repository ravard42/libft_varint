#ifndef NNAUMENK_LIBFT_H
# define NNAUMENK_LIBFT_H

# include "libft.h"
# include "ft_bigint.h"
# include "ft_bigint_struct.h"

void			ft_bzero(void *s, size_t n);
void			ft_memrev(void *mem, size_t num);
void			ft_pow_mod(t_bigint *r, t_bigint *num, t_bigint *pow, t_bigint *mod);


#endif
