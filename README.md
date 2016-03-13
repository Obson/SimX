# SimX
SimX is a simple economic modelling system written in Code::Blocks using
the wxSmith framework.

It has has been developed in Linux and hasn't been compiled for any other
OS. The current version is pre-alpha and is not guaranteed to work, even
under Linux!

Conceptually the model is based on the idea of sectoral balances and inter-
sectoral flows. It simply provides a mechanism for defining the sectors
we are interested in, the flows between them, and the relationships between
these quantities (expressed as a set of equations). The model is constructed
to move through a sequence of states, where each state in determined from
the immediately preceding state as defined by equations.

'Probes' and 'parameters' are also allowed. A probe is a quantity that is
dependent on (is a function of) other quantities but no quantities are dependent
on it. A parameter is in a sense a 'constant', that is, its numerical value
is fixed at the start of a run, but is thereafter unchanged. Parameters
can be set quickly and easily, so that a run can be repeated (or extended)
with different parameter values, and the effect on the model's behaviour
monitored.

There is currently no online help (none of the 'Help' buttons actuall do
anything) and there is no tutorial. I have however written a document that
describes its use  in investigating some of the propositions on Modern Money
Theory, and plan to adapt this as an introductory tutorial.

More info will follow later...
