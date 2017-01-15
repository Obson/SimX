# SimX
SimX is a simple economic modelling system written in C++ using Code::Blocks
and wxWidgets.

It has has been developed in Linux and hasn't so far been compiled for any other
OS. The current version is pre-alpha and is not guaranteed to work, even
under Linux!

Conceptually the model is based on the idea of sectoral balances and inter-sectoral
flows. It simply provides a mechanism for defining the sectors we are interested
in, the flows between them, and the relationships between these quantities
(expressed as a set of equations). The model is constructed to move through
a sequence of states (representing intervals of time), where each state is
determined from its immediately preceding state, as defined by equations.
Any of the quantities can be graphed against time.

'Probes' and 'parameters' are also allowed. A probe is a quantity that is
dependent on (is a function of) other quantities but no quantities are dependent
on it. A parameter is in a sense a 'constant', that is, its numerical value
is fixed at the start of a run, but is thereafter unchanged. Parameters
can be set quickly and easily, so that a run can be repeated (or extended)
with different parameter values, and the effect of the changes on the model's
behaviour monitored.

There is currently no online help (none of the 'Help' buttons actually does
anything) and there is no tutorial as yet. I am however writing a document
Chapter 1 of which describes its use  in investigating some of the propositions
of Modern Money Theory. It's included
here as [Comprehensible Macro-Economics] (https://github.com/Obson/SimX/blob/master/comprehensible-macro-economics-2017-1.pdf) 

See [the wiki] (https://github.com/Obson/SimX/wiki) for more information...
