#ifndef EMP_SEMIHONEST_H__
#define EMP_SEMIHONEST_H__
#include "emp-sh2pc/sh_gen.h"
#include "emp-sh2pc/sh_eva.h"

namespace emp {

template<typename IO>
inline SemiHonestParty<IO>* setup_semi_honest(IO* io, int party, int batch_size = 1024*16, IO* trustedThirdPartyIO=nullptr) {

	if(party == ALICE) {
		HalfGateGen<IO> * t = new HalfGateGen<IO>(io);
		CircuitExecution::circ_exec = t;
		ProtocolExecution::prot_exec = new SemiHonestGen<IO>(io, trustedThirdPartyIO, t);
	} else {
		HalfGateEva<IO> * t = new HalfGateEva<IO>(io);
		CircuitExecution::circ_exec = t;
		ProtocolExecution::prot_exec = new SemiHonestEva<IO>(io, trustedThirdPartyIO, t);
	}
	return (SemiHonestParty<IO>*)ProtocolExecution::prot_exec;
}

inline void finalize_semi_honest() {
	delete CircuitExecution::circ_exec;
	delete ProtocolExecution::prot_exec;
}

}
#endif
