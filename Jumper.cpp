#include "Jumper.h"

#define FVF_VERTEX D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1

struct _VERTEX {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 norm;
	float tu;
	float tv;
};

Jumper::Jumper(void) {
	D3DXMatrixIdentity(&m_mLocal);
	ZeroMemory(&m_mtrl, sizeof(m_mtrl));
	v_x = v_z = 0;
	m_pJumperMesh = NULL;
}

Jumper::Jumper(const char* jumperImageFileName) {
	Jumper();
	this->jumperImageFileName = jumperImageFileName;
}

Jumper::~Jumper(void) {

}

bool Jumper::create(IDirect3DDevice9* pDevice) {
	if (!pDevice) return false;

	m_mtrl.Diffuse = d3d::WHITE;
	m_mtrl.Ambient = d3d::WHITE;
	m_mtrl.Specular = d3d::WHITE;
	m_mtrl.Emissive = d3d::BLACK;
	m_mtrl.Power = 100.0f;

	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	this->m_pJumperMesh = _createMappedBox(pDevice);

	string filePath = "./image/" + jumperImageFileName + ".bmp";
	if (FAILED(D3DXCreateTextureFromFile(pDevice, filePath.c_str(), &Tex))) {
		return false;
	}

	return true;
}

void Jumper::destroy(void) {
	if (m_pJumperMesh != NULL) {
		m_pJumperMesh->Release();
		m_pJumperMesh = NULL;
	}
}

void Jumper::draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld) {
	if (NULL == pDevice)
		return;

	pDevice->SetTransform(D3DTS_WORLD, &mWorld);
	pDevice->MultiplyTransform(D3DTS_WORLD, &m_mLocal);
	//pDevice->MultiplyTransform(D3DTS_WORLD, &ballRoll);
	pDevice->SetTexture(0, Tex);
	pDevice->SetMaterial(&m_mtrl);
	m_pJumperMesh->DrawSubset(0);
}

bool Jumper::hasIntersected(Platform& platform) {
	D3DXVECTOR3 cord = this->getPosition();
	D3DXVECTOR3 platform_cord = platform.getPosition();

	double xDistance = cord.x - platform_cord.x;
	double zDistance = cord.z - platform_cord.z;

	if (0 < xDistance && xDistance < WIDTH) {

	}

	double xDistance = abs((cord.x - platform_cord.x) * (cord.x - platform_cord.x));
	double zDistance = abs((cord.z - platform_cord.z) * (cord.z - platform_cord.z));
	double totalDistance = sqrt(xDistance + zDistance);

	if (totalDistance < (this->getRadius() + ball.getRadius())) {
		return true;
	}

	return false;
}

double Jumper::getVelocity_X() {

}

double Jumper::getVelocity_Z() {

}

void Jumper::setPower(double vx, double vz) {

}

const D3DXMATRIX& Jumper::getLocalTransform(void) const {

}

void Jumper::setLocalTransform(const D3DXMATRIX& mLocal) {

}

D3DXVECTOR3 Jumper::getPosition() const {

}

void Jumper::adjustPosition(Jumper& jumper) {

}

void Jumper::setPosition(float x, float y, float z) {

}

LPD3DXMESH Jumper::_createMappedBox(IDirect3DDevice9* pDev) {
	LPD3DXMESH mesh;
	if (FAILED(D3DXCreateSphere(pDev, 50, 50, 50, &mesh, NULL)))
		return nullptr;

	LPD3DXMESH texMesh;
	if (FAILED(mesh->CloneMeshFVF(D3DXMESH_SYSTEMMEM, FVF_VERTEX, pDev, &texMesh)))
		return mesh;

	mesh->Release();

	struct _VERTEX* pVerts;
	if (SUCCEEDED(texMesh->LockVertexBuffer(0, reinterpret_cast<void**>(&pVerts)))) {
		int numVerts = texMesh->GetNumVertices();

		for (int i = 0; i < numVerts; i++) {
			pVerts->tu = asinf(pVerts->norm.x) / D3DX_PI + 0.5f;
			pVerts->tv = asinf(pVerts->norm.y) / D3DX_PI + 0.5f;

			pVerts++;
		}
		texMesh->UnlockVertexBuffer();
	}

	return texMesh;
}

void Jumper::disable() noexcept {

}

void Jumper::enable() noexcept {

}

int Jumper::getDisableTurn() const noexcept {

}

bool Jumper::isDisabled() const noexcept {

}