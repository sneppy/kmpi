#include "alg/node.h"

#include <chrono>

int main(int argc, char **argv)
{
	// Init command line
	CommandLine gCommandLine(argc, argv);

    // TODO
    // -> generalize types(both float32 and float64)
    // -> generalize to n-dimensional data point
    // -> benchmark in LAN with and without -03
    MPI::init(&argc, &argv);

    // these are read from command line args
    uint32 k = 5;
    uint32 maxNumEpochs = 100;
    float32 tol = 1e-4;

	gCommandLine.getValue("--num-clusters", k);
	gCommandLine.getValue("--max-iter", maxNumEpochs);
	gCommandLine.getValue("--tolerance", tol);

    Node thisNode(k, tol);

    // Generate dummy dataset
    //writeDatasetToFile(generateDummyDataset());

    // Assign equally data points to each machine
    thisNode.loadPoints();

    // Set initial centroids
    thisNode.selectRandomCentroids();

    // Receive Initial centroids
    thisNode.receiveGlobalCentroids();

    for (uint32 epoch = 1; epoch <= maxNumEpochs; epoch++) {
        // Compute memberships of each point and compute local centroids according to local membership view
        thisNode.optimize();

        // Compute new centroids
        thisNode.updateGlobal(epoch);

        // Receive current centroids and loss from previous epoch
        thisNode.receiveGlobal(epoch);

        // Check convergence
        /* if (thisNode.hasConverged()) {
            break;
        } */
    }

    thisNode.finalize();
    thisNode.writeResults();

    MPI::shutdown();

    return 0;
}